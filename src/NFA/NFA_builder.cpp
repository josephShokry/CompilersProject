//
// Created by alsay on 11/29/2024.
//

#include "NFA_builder.h"
#define conc_symbol "#"
#define eps_ch '$'
#define eps_str "$"
#define init_Id (-1)


/*
 *  Steps to build the NFA:
 *  1. Extract the rules from the file : extract_rules(rules_file_path)
 *  2. Split the rules into tokens and regex : split_rules()
 *  3. Set the pre-defined tokens : set_pre_defined_tokens()
 *  4. Map the regex to tokens : map_regex_to_tokens()
 *  5. Create the NFAs for each token : create_NFAs()
 *  6. Combine the NFAs into a single NFA : combined_nfa()
 */
Node *NFA_builder::deep_copy_node(Node *original, unordered_map<Node *, Node *> &copied_nodes) {
    if (copied_nodes.contains(original)) {
        return copied_nodes[original];
    }

    Node *copy = new Node(original->get_id(), original->get_is_start(), original->get_is_accepting());
    copied_nodes[original] = copy;

    for (auto &[ch, neighbours]: original->get_neighbours()) {
        for (Node *neighbour: neighbours) {
            copy->add_neighbour(ch, deep_copy_node(neighbour, copied_nodes));
        }
    }

    return copy;
}

// Method to deep copy an NFA
NFA NFA_builder::deep_copy_nfa(NFA original) {
    unordered_map<Node *, Node *> copied_nodes;
    Node *new_start = deep_copy_node(original.get_start_node(), copied_nodes);
    Node *new_end = copied_nodes[original.get_end_node()];
    return {new_start, new_end};
}

void NFA_builder::delete_character_from_string(string &rule, const char letter) {
    erase(rule, letter);
}

// Method to extract rules from the file
void NFA_builder::extract_rules(string rules_file_path) {
    vector<string> lines;
    ifstream file(rules_file_path);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << rules_file_path << std::endl;
    }
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    this->rules = lines;
}

vector<string> NFA_builder::add_concatenation_symbol(vector<string> tokens) {
    if (tokens.size() == 0) {
        assert("Error, token is empty");
    }
    vector<string> conc_added_tokens;
    unordered_set<string> not_conc_left = {"(", "|"};
    unordered_set<string> not_conc_right = {")", "|", "*", "+"};
    unordered_set<string> operations = get_operations();

    for (int i = 0; i < tokens.size(); i++) {
        if (operations.contains(tokens[i])) {
            conc_added_tokens.push_back(tokens[i]);
            continue;
        }
        // Look left
        if (i - 1 >= 0 && !not_conc_left.contains(tokens[i - 1]) && conc_added_tokens.back() != conc_symbol) {
            conc_added_tokens.push_back(conc_symbol);
        }
        conc_added_tokens.push_back(tokens[i]);
        // look Right
        if (i + 1 < tokens.size() && !not_conc_right.contains(tokens[i + 1])) {
            conc_added_tokens.push_back(conc_symbol);
        }
    }
    return conc_added_tokens;
}


vector<string> NFA_builder::split_to_characters(string input) {
    vector<string> result;
    for (const char ch: input) {
        result.push_back(string(1, ch));
    }
    return result;
}


void NFA_builder::split_keywords_and_punctuation(string rule, int priority) {
    bool keyword = rule[0] == '{';
    rule.erase(0, 1);
    rule.pop_back();
    // delete_character_from_string(rule, '\\');
    int i = 0;
    while (isspace(rule[i])) {
        i++;
    }
    string token;
    for (; i < rule.size(); i++) {
        if (isspace(rule[i])) {
            if (!token.empty()) {
                if (token[0] == '\\') {
                    token = token.substr(1);
                }
                token_to_priority[token] = priority;
                vector<string> after_splitting = split_to_characters(token);
                if (keyword) {
                    token_to_regex_split[token] = add_concatenation_symbol(after_splitting);
                } else {
                    token_to_regex_split[token] = after_splitting;
                }
                token = "";
            }
        } else {
            token += rule[i];
        }
    }

    if (!token.empty()) {
        if (token[0] == '\\') {
            token = token.substr(1);
        }
        token_to_priority[token] = priority;
        vector<string> after_splitting = split_to_characters(token);
        if (keyword) {
            token_to_regex_split[token] = add_concatenation_symbol(after_splitting);
        } else {
            token_to_regex_split[token] = after_splitting;
        }
    }
}

void NFA_builder::split_regular_definitions_and_expressions(string rule, int priority) {
    string token, rule_without_spaces = utils::remove_spaces_from_regex(rule);
    rule_without_spaces = std::regex_replace(rule_without_spaces, std::regex("\\L"), eps_str);
    string rule_after_resolving_ranges = utils::resolve_range(rule_without_spaces);
    // delete_character_from_string(rule_after_resolving_ranges, '\\');

    int value_start_index = 0;
    for (int i = 0; i < rule_after_resolving_ranges.size(); i++) {
        if (rule_after_resolving_ranges[i] == ':' || rule_after_resolving_ranges[i] == '=') {
            value_start_index = i + 1;
            break;
        }
        token += rule_after_resolving_ranges[i];
    }
    string value = rule_after_resolving_ranges.substr(value_start_index);
    token_to_priority[token] = priority;
    token_to_regex_split[token] = vector(1, value);
}

void NFA_builder::split_rules() {
    for (int i = 0; i < rules.size(); i++) {
        if (isalpha(rules[i][0])) {
            split_regular_definitions_and_expressions(rules[i], i);
        } else {
            split_keywords_and_punctuation(rules[i], i);
        }
    }
}

void NFA_builder::set_pre_defined_tokens() {
    for (auto [token, vec]: token_to_regex_split) {
        pre_defined_tokens.insert(token);
    }
}

unordered_set<string> NFA_builder::get_operations() {
    unordered_set<string> operations = {"(", "|", ")", "*", "+"};
    return operations;
}

vector<string> NFA_builder::tokenize_rule(const string input) {
    vector<string> tokens; // List of tokens
    size_t start = 0;

    while (start < input.size()) {
        string longestMatch;
        size_t end = start;

        // Check for escaped characters
        if (input[start] == '\\' && start + 1 < input.size()) {
            tokens.push_back(input.substr(start, 2)); // Add the escaped character as a token
            start += 2; // Move past the escaped character
            continue;
        }

        // Find the longest matching predefined token
        while (end < input.size()) {
            string candidate = input.substr(start, end - start + 1);
            if (pre_defined_tokens.find(candidate) != pre_defined_tokens.end()) {
                longestMatch = candidate;
            }
            end++;
        }

        if (!longestMatch.empty()) {
            tokens.push_back(longestMatch); // Add valid token
            start += longestMatch.size(); // Move past the matched token
        } else {
            // If no predefined token matches, treat the current character as a token
            tokens.push_back(string(1, input[start]));
            start++;
        }
    }

    return tokens;
}

void NFA_builder::map_regex_to_tokens() {
    for (auto &[token, v]: token_to_regex_split) {
        if (v.size() == 1) {
            string regex_to_be_tokenized = v.back();
            v.pop_back();
            vector<string> tokens = tokenize_rule(regex_to_be_tokenized);
            v = add_concatenation_symbol(tokens);
        }
    }
}

NFA NFA_builder::create_single_char_NFA(string ch) {
    // Id is arbitrary here -> will be assigned after the combined NFA is constructed.
    Node *start = new Node(init_Id, true, false);
    Node *end = new Node(init_Id, false, true);
    assert(ch.size() == 1);
    start->add_neighbour(ch[0], end);

    return {start, end};
}

NFA NFA_builder::join(NFA NFA_1, NFA NFA_2) {
    Node *start = new Node(init_Id, true, false);
    Node *end = new Node(init_Id, false, true);

    // Add epsilon transitions from the new start node to the start nodes of NFA_1 and NFA_2
    start->add_neighbour(eps_ch, NFA_1.get_start_node());
    start->add_neighbour(eps_ch, NFA_2.get_start_node());

    // Make the old start nodes non-start nodes
    NFA_1.get_start_node()->set_is_start(false);
    NFA_2.get_start_node()->set_is_start(false);

    // Add epsilon transitions from the end nodes of NFA_1 and NFA_2 to the new end node
    NFA_1.get_end_node()->add_neighbour(eps_ch, end);
    NFA_2.get_end_node()->add_neighbour(eps_ch, end);

    // Make the old end nodes non-accepting nodes
    NFA_1.get_end_node()->set_is_accepting(false);
    NFA_2.get_end_node()->set_is_accepting(false);

    return {start, end};
}

NFA NFA_builder::concatenate(NFA NFA_1, NFA NFA_2) {
    NFA_1.get_end_node()->concatenate_neighbours(NFA_2.get_start_node()->get_neighbours());
    NFA_1.get_end_node()->set_is_accepting(false);
    delete(NFA_2.get_start_node());
    return {NFA_1.get_start_node(), NFA_2.get_end_node()};
}

NFA NFA_builder::kleene_closure(NFA NFA_1) {
    Node *start = new Node(init_Id, true, false);
    Node *end = new Node(init_Id, false, true);

    // Add epsilon transitions from the new start node to the start node of NFA_1 and to the new end node
    start->add_neighbour(eps_ch, NFA_1.get_start_node());
    start->add_neighbour(eps_ch, end);

    // Add epsilon transitions from the end node of NFA_1 to its start node and to the new end node
    NFA_1.get_end_node()->add_neighbour(eps_ch, NFA_1.get_start_node());
    NFA_1.get_end_node()->add_neighbour(eps_ch, end);

    // Make the old start node non-starting
    NFA_1.get_start_node()->set_is_start(false);

    // Make the old end node non-accepting
    NFA_1.get_end_node()->set_is_accepting(false);

    return {start, end};
}

NFA NFA_builder::kleene_plus(NFA NFA_1) {
    Node *start = new Node(init_Id, true, false);
    Node *end = new Node(init_Id, false, true);

    // Add epsilon transitions from the new start node to the start node of NFA_1 and to the new end node
    start->add_neighbour(eps_ch, NFA_1.get_start_node());

    // Add epsilon transitions from the end node of NFA_1 to its start node and to the new end node
    NFA_1.get_end_node()->add_neighbour(eps_ch, NFA_1.get_start_node());
    NFA_1.get_end_node()->add_neighbour(eps_ch, end);

    // Make the old start node non-starting
    NFA_1.get_start_node()->set_is_start(false);

    // Make the old end node non-accepting
    NFA_1.get_end_node()->set_is_accepting(false);

    return {start, end};
}


/*
 *  Recursive function to build the NFA for a given sub token.
 *  @Param token: The sub token i.e (unit in token split vector) to build the NFA for.
 */
NFA NFA_builder::get_NFA(const string &token) {
    // Token splitting and operator definitions

    // Check if token has already been processed
    if (token_to_NFA.contains(token)) {
        // return token_to_NFA[token];
        return deep_copy_nfa(token_to_NFA[token]);
    }

    // Base case: handle single-character sub tokens
    if (token.size() == 1 && !token_to_regex_split.contains(token)) {
        return create_single_char_NFA(token);
    }

    // Special case for []
    if (token_to_regex_split.contains(token) && token_to_regex_split[token].size() == 1 && (
            token == token_to_regex_split[token].back())) {
        token_to_NFA[token] = create_single_char_NFA(token);
        return deep_copy_nfa(token_to_NFA[token]);
    }

    // Handle keywords preceded by "\"
    if (token.size() == 2 && token[0] == '\\') {
        return create_single_char_NFA(token.substr(1));
    }
    const vector<string> &tokens_vec = token_to_regex_split[token];
    const unordered_map<string, int> operations = {
        {"*", 0}, {"+", 1}, {conc_symbol, 2}, {"|", 3}, {"(", 4}
    };

    stack<NFA> val; // Stack to hold NFAs
    stack<string> op; // Stack to hold operators

    // Helper function to process the top operator in the stack
    auto process_operator = [&]() {
        string top_op = op.top();
        op.pop();

        if (top_op == conc_symbol) {
            NFA NFA_2 = val.top();
            val.pop();
            NFA NFA_1 = val.top();
            val.pop();
            val.push(concatenate(NFA_1, NFA_2));
        } else if (top_op == "|") {
            NFA NFA_2 = val.top();
            val.pop();
            NFA NFA_1 = val.top();
            val.pop();
            val.push(NFA_builder::join(NFA_1, NFA_2));
        } else if (top_op == "*") {
            NFA NFA_1 = val.top();
            val.pop();
            val.push(kleene_closure(NFA_1));
        } else if (top_op == "+") {
            NFA NFA_1 = val.top();
            val.pop();
            val.push(kleene_plus(NFA_1));
        }
    };

    // Process each sub-token in the token vector representing the regex
    for (const string &sub_token: tokens_vec) {
        if (operations.contains(sub_token) || sub_token == ")") {
            if (sub_token == "(") {
                op.push(sub_token);
            } else if (sub_token == ")") {
                while (!op.empty() && op.top() != "(") {
                    process_operator();
                }
                if (!op.empty()) op.pop(); // Remove "(" from stack
            } else {
                while (!op.empty() && operations.at(op.top()) <= operations.at(sub_token)) {
                    process_operator();
                }
                op.push(sub_token);
            }
        } else {
            // If it's a value, push the corresponding NFA
            val.push(get_NFA(sub_token));
        }
    }

    // Process remaining operators
    while (!op.empty()) {
        process_operator();
    }

    if (!token_to_NFA.contains(token)) {
        token_to_NFA[token] = val.top();
    }
    return deep_copy_nfa(token_to_NFA[token]);
}


void NFA_builder::create_NFAs() {
    for (auto &[token, _]: token_to_regex_split) {
        get_NFA(token);
        NFA nfa = token_to_NFA[token];
        nfa.get_end_node()->add_token(token);
    }
}

NFA NFA_builder::combined_nfa() {
    int start_id = 0;

    Node *start = new Node(start_id, true, false);
    Node *end = nullptr;

    for (auto &[token, nfa]: token_to_NFA) {
        start->add_neighbour(eps_ch, nfa.get_start_node());
        nfa.get_start_node()->set_is_start(false);
        end = nfa.get_end_node();
    }

    auto set_ids = std::function<void(Node *, int &)>{};
    set_ids = [&](Node *node, int &id) {
        node->set_id(id++);
        for (auto &[_, neighbours]: node->get_neighbours()) {
            for (Node *neighbour: neighbours) {
                if (neighbour->get_id() == init_Id) {
                    set_ids(neighbour, id);
                }
            }
        }
    };
    set_ids(start, start_id);
    return {start, end};
}

map<string, vector<string> > NFA_builder::get_token_to_regex_split() {
    return token_to_regex_split;
}

map<string, int> NFA_builder::get_priority() {
    return token_to_priority;
}
