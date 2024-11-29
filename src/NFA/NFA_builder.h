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
    map<string, vector<string>> token_to_regex_split;
    // map<string, NFA> token_to_NFA;
    vector<string> rules;
    void split_keywords_and_punctuation(string rule, int priority);
    void split_regular_definitions_and_expressions(string rule, int priority);
    vector<string>split_to_characters(string input);
    vector<string> add_concatenation_symbol(vector<string> tokens);

public:
    void extract_rules(string rules_file_path);
    void split_rules();
    void split_token_regex();
    void split_reserved_or_punc();
    void split_reg_def();
    void make_token_nfa();
    vector<string> tokenize_rules(const string &input, const unordered_set<string> &predefinedTokens);
    // NFA combined_nfa();
};



#endif //NFA_BUILDER_H
