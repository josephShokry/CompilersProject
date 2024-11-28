// lexical_analyser.h
#ifndef LEXICAL_ANALYSER_H
#define LEXICAL_ANALYSER_H

#include <string>
#include <bits/stdc++.h>

using namespace std;

class lexical_analyser {
private:
    // Reads the contents of a file (returns NULL for now, to be implemented)
    string read_file();

    // Constructs a single start NFA from the rules (to be implemented)
    Node rules_to_nfa();

    // Converts the NFA to a DFA (to be implemented)
    void nfa_to_dfa(Node nfa_start_node);

    // Minimizes the DFA (to be implemented)
    void minimize_dfa();

public:
    // Parses the rules of the language from a specified file path
    vector<string> extract_rules(string rules_file_path);

    // Parses the code to be analyzed, using the previously set rules file path
    vector<string> set_code(string code_file_path);

    // Retrieves the next token (currently returns NULL)
    string get_next_token();

    // Check if the lexical analyser can get more token or not
    bool has_next();

    lexical_analyser(const string &rules_file_path, const string &code_file_path);
};

#endif // LEXICAL_ANALYSER_H
