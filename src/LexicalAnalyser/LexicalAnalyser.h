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


public:

    void extract_code_text(string file_path_to_code_text) {
        ifstream file(file_path_to_code_text);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << file_path_to_code_text << std::endl;
        }

        string text;
        string line;
        while (getline(file, line)) {
            text += line;  // Concatenate lines directly
        }
        file.close();
        cout<<text;
        this->code_text = text;
    }
    lexical_analyser(DFA dfa, string file_path_to_code_text)
        : dfa(dfa) {
        extract_code_text(file_path_to_code_text);
    }

    // to get the next token
   string get_next_token() {
        int current_state_id = dfa.get_starting_state_id();
        stack<int> new_states_ids;
        int start_index = current_index;
        while (true) {
            int next_node_id = dfa.getNextNodeId(current_state_id, code_text[current_index]);
            if (next_node_id == -1) break;
            new_states_ids.push(next_node_id);
            current_state_id = next_node_id;
            current_index++;
        }

        while (!new_states_ids.empty()) {
            int next_node_id = new_states_ids.top();
            new_states_ids.pop();
            if (dfa.isAcceptingState(next_node_id)) {
                // token priority
                string token = code_text.substr(start_index, current_index - start_index);
                cout<< "Token found starting from index: "<< start_index <<" the token: "<< token<<"\n";
                return token ;
            }
            current_index--;
        }
        // if (new_states_ids.empty()) {
        //     cout << "No token found starting from index: "<< start_index <<"with char: "<< code_text[start_index]<<"\n";
        //     current_index++;
        // }
        cout << "No token found starting from index: "<< start_index <<" with char: "<< code_text[start_index]<<"\n";
        current_index++;
        return "";
    }

    // Check if the lexical analyser can get more token or not
    bool has_next() {
        return current_index < code_text.length();
    }

    void reset_index() {
        current_index = 0;
    }
    void get_all_tokens() {
        while (has_next()) {
            get_next_token();
        }
        reset_index();
    }
};
