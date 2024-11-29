#include <string>
#include <vector>
#include <bits/stdc++.h>


using namespace std;

class lexical_analyser {

private:
    string code_text = "";
    map<string,string> symbol_table;
    int start_indx = 0;

    // Reads the contents of a file (returns NULL for now, to be implemented)
    string read_file(string file_path) {
        return NULL;
    }

    // to set the rules of the language
    vector<string> extract_rules(string rules_file_path) {

    }

    // to set the code that being analyzed against the ruled added previously
    vector<string> set_code(string code_file_path) {
        code_text = read_file(code_file_path);
        return NULL;
    }

    // construct a single start NFA from the rules
    NFA rules_to_nfa() {

    }

    // construct a DFA out of NFA
    DFA nfa_to_dfa(NFA nfa) {

    }

public:
    // Constructor to parse the rules and code files
    lexical_analyser(const string &rules_file_path, const string &code_file_path) {
        extract_rules(rules_file_path);
        set_code(code_file_path);
    }

    // to get the next token
    string get_next_token() {
        return NULL;
    }

    // Check if the lexical analyser can get more token or not
    bool has_next() {
        return !code_text.empty();
    }
};
