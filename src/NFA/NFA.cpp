// NFA.cpp
#include "NFA.h"

#include <vector>
#include <bits/stdc++.h>

#include "NFA_builder.h"
#include "../Node/Node.h"

using namespace std;

set<Node *> NFA::get_equivilant_nodes(set<Node *> current_nodes) {
    set<Node *> next = current_nodes;
    int size = next.size();
    while (true) {
        set<Node *> s = get_next_nodes(next, eps);
        next.insert(s.begin(), s.end());
        if (next.size() == size)break;
        size = next.size();
    }

    return next;
}

vector<char> NFA::get_transition_chars(NFA_builder nfa_builder) {
    map<string, vector<string> > token_to_regex_split = nfa_builder.get_token_to_regex_split();
    unordered_set<char> operations = {'(', '|', ')', '*', '+', '#', '$'};
    set<char> transition_characters;
    for (auto &[token, v] : token_to_regex_split) {
        for (auto &x : v) {
            if (x.size() == 1 && operations.find(x[0]) == operations.end()) {
                transition_characters.insert(x[0]);
            }else if (x.size() == 2 && x[0] == '\\' && operations.find(x[1]) == operations.end()) {
                transition_characters.insert(x[1]);
            }
        }
    }
    vector<char> transition_vector(transition_characters.begin(), transition_characters.end());
    return transition_vector;
}

set<Node *> NFA::get_next_nodes(set<Node *> current_nodes, char transition) {
    set<Node *> sett;

    for (Node *node: current_nodes) {
        if (node->has_transition(transition)) {
            vector<Node *> nei = node->get_neighbour(transition);
            sett.insert(nei.begin(), nei.end());
        }
    }
    return sett;
}

Node *NFA::get_start_node() {
    return start_node;
}

void NFA::set_start_node(Node *start_node) {
    this->start_node = start_node;
}

Node *NFA::get_end_node() {
    return end_node;
}

void NFA::set_end_node(Node *end_node) {
    this->end_node = end_node;
}
