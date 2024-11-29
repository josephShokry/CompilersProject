//
// Created by alsay on 11/29/2024.
//

#include "NFA_builder.h"
#define conc_symbol "#"

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
    unordered_set<string> operations = {"(", "|", ")", "*", "+"};

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
    int i = 1;

    while (!isspace(rule[i])) {
        i++;
    }

    string token;

    for (; i < rule.size(); i++) {
        if (isspace(rule[i])) {
            if (!token.empty()) {
                token_to_priority[token] = priority;
                vector<string> after_splitting = split_to_characters(token);
                if (keyword) {
                    token_to_regex_split[token] = add_concatenation_symbol(after_splitting);
                }
                else {
                    if (after_splitting[0][0] == '\\'){
                        after_splitting[0].erase(0, 1);
                    }
                    token_to_regex_split[token] = after_splitting;
                }
            }
        }
    }
}

void NFA_builder::split_regular_definitions_and_expressions(string rule, int priority) {
    string token, rule_without_spaces = utils::remove_spaces_from_regex(rule);
    int value_start_index = 0;
    for (int i = 0 ; i < rule_without_spaces.size() ; i++) {
        if (rule_without_spaces[i] == ':' || rule_without_spaces[i] == '=') {
            value_start_index = i+1;
            break;
        }
        token += rule_without_spaces[i];
    }
    string value = rule_without_spaces.substr(value_start_index);
    token_to_priority[token] = priority;
    token_to_regex_split[token] = vector(1, value);
}

void NFA_builder::split_rules() {
    for (int i = 0 ; i < rules.size() ; i++) {
        if (isalpha(rules[i][0])) {
            split_regular_definitions_and_expressions(rules[i], i);
        } else {
            split_keywords_and_punctuation(rules[i], i);
        }
    }
}

// Method to split tokens and regex
void NFA_builder::split_token_regex() {
}

// Method to split reserved keywords or punctuation
void NFA_builder::split_reserved_or_punc() {
}

// Method to split regular definitions
void NFA_builder::split_reg_def() {
}

// Method to construct individual token NFAs
void NFA_builder::make_token_nfa() {
}

// Method to combine individual NFAs into a single NFA
// NFA NFA_builder::combined_nfa() {
//     return NFA(); // Return a default NFA object (replace with logic if needed)
// }

vector<string> NFA_builder::tokenize_rules(const string &input, const unordered_set<string> &predefinedTokens) {
    vector<string> tokens; // List of tokens
    size_t start = 0;

    while (start < input.size()) {
        string longestMatch;
        size_t end = start;

        // Find the longest matching predefined token
        while (end < input.size()) {
            string candidate = input.substr(start, end - start + 1);
            if (predefinedTokens.find(candidate) != predefinedTokens.end()) {
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
