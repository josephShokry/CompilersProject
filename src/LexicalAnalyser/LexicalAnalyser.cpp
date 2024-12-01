#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "../Node/Node.h"
#include "../NFA/NFA.h"
#include "../DFA/DFA.h"

using namespace std;

class lexical_analyser {

private:
    DFA dfa;
    string code_text = "";
    map<string,string> symbol_table;
    int current_index = 0;


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
        return vector<string>(NULL);
    }

    // construct a single start NFA from the rules
    NFA rules_to_nfa() {

    }

    // construct a DFA out of NFA
    DFA nfa_to_dfa(NFA nfa) {

    }



public:


    void set_dfa(DFA dfa) {
        this->dfa = dfa;
    }
    DFA get_dfa() {
        return this->dfa;
    }

    // Constructor to parse the rules and code files
    lexical_analyser(const string &rules_file_path, const string &code_file_path) {
        extract_rules(rules_file_path);
        set_code(code_file_path);
    }

    // to get the next token
    string get_next_token() {
        int current_state_id = dfa.getStartingStateId();
        stack<int> new_states_ids;
        int start_indx = current_index;
        while (true) {
                int next_node_id = dfa.getNextNodeId(current_state_id, code_text[current_index]);
                if (next_node_id == -1) break;
                new_states_ids.push(next_node_id);
                current_state_id = next_node_id;
                current_index++;
        }
        if (new_states_ids.empty()) {
            cout << "No token found starting from index: "<< start_indx <<"with char: "<< code_text[start_indx]<<"\n";
            current_index++;
        }
        while (!new_states_ids.empty()) {
            int next_node_id = new_states_ids.top();
            new_states_ids.pop();
            if (dfa.isAcceptingState(next_node_id)) {
                // token priority
                string token = code_text.substr(start_indx, current_index - start_indx + 1);
                cout<< "Token found starting from index: "<< start_indx <<"the token: "<< token<<"\n";
                return token ;
            }
            current_index--;
        }
        cout << "No token found starting from index: "<< start_indx <<"with char: "<< code_text[start_indx];
        current_index++;
        return "";
    }

    // Check if the lexical analyser can get more token or not
    bool has_next() {
        return current_index < code_text.length();
    }
};
