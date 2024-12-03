//
// Created by alsay on 11/29/2024.
//

#ifndef NFA_BUILDER_H
#define NFA_BUILDER_H

#include "NFA.h"
#include "../Utils/utils.h"
#include <bits/stdc++.h>
using namespace std;


class NFA_builder {
private:
    map<string, int> token_to_priority;
    map<string, vector<string> > token_to_regex_split;
    map<string, NFA> token_to_NFA;
    vector<string> rules;
    unordered_set<string> pre_defined_tokens;

    void delete_character_from_string(string &rule, const char letter);

    void split_keywords_and_punctuation(string rule, int priority);

    void split_regular_definitions_and_expressions(string rule, int priority);

    vector<string> split_to_characters(string input);

    vector<string> add_concatenation_symbol(vector<string> tokens);

    static unordered_set<string> get_operations();

    vector<string> tokenize_rule(const string input);

    NFA get_NFA(const string &token);

    NFA create_single_char_NFA(string ch);

    NFA kleene_closure(NFA NFA_1);

    NFA concatenate(NFA NFA_1, NFA NFA_2);

    NFA join(NFA NFA_1, NFA NFA_2);

    NFA kleene_plus(NFA NFA_1);

public:
    void extract_rules(string rules_file_path);

    void split_rules();

    void set_pre_defined_tokens();


    // void split_token_regex();
    //
    // void split_reserved_or_punc();
    //
    // void split_reg_def();
    //
    // void make_token_nfa();

    void map_regex_to_tokens();

    void create_NFAs();

    NFA combined_nfa();

    map<string, vector<string> > get_token_to_regex_split();

    map<string, int> get_priority();

    NFA deep_copy_nfa(NFA original);

    Node *deep_copy_node(Node *original, unordered_map<Node *, Node *> &copied_nodes);

};


#endif //NFA_BUILDER_H
