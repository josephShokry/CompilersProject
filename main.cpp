#include "bits/stdc++.h"
#include "src/DFA/DFA.h"
#include "src/Utils/utils.h"
#include "src/NFA/NFA_builder.h"
using namespace std;

#define conc_symbol "#"

void bfs_co(NFA nfa, map<string, int> priority) {
    unordered_set<int> visited;
    queue<Node*> q;
    q.push(nfa.get_start_node());
    visited.insert(nfa.get_start_node()->get_id());

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << "Node ID: " << current->get_id();
        if (current->get_is_start()) {
            cout << " (Start)";
        }
        if (current->get_is_accepting()) {
            cout << " (Accepting) "<<priority[current->get_tokens()[0]]<<" "<<current->get_tokens()[0];
        }
        cout << endl;

        for (const auto& [symbol, neighbours] : current->get_neighbours()) {
            for (Node* neighbour : neighbours) {
                cout << "  --" << symbol << "--> Node ID: " << neighbour->get_id() << endl;
                if (!visited.contains(neighbour->get_id())) {
                    visited.insert(neighbour->get_id());
                    q.push(neighbour);
                }
            }
        }
    }
}

int main() {
    NFA_builder nfa_builder;

    nfa_builder.extract_rules("../input_rules.txt");
    nfa_builder.split_rules();
    nfa_builder.set_pre_defined_tokens();
    nfa_builder.map_regex_to_tokens();
    // Print tokens
    for (auto &[token, v] : nfa_builder.get_token_to_regex_split()) {
        cout << "Token : [" << token << "] -> ";
        for (auto &x : v) {
            cout << x << " ";
        }
        cout << endl;
    }
    nfa_builder.create_NFAs();
    NFA nfa = nfa_builder.combined_nfa();
    bfs_co(nfa, nfa_builder.get_priority());

    DFA dfa(nfa);

    dfa.print_transition_table();
    cout<<"###########3"<<endl;
    dfa.minimize();
    dfa.print_transition_table();
}
