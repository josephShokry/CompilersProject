// NFA.cpp
#include "NFA.h"

// Constructor for NFA, which initializes the NFA with given regular definitions
// NFA::NFA(vector<string> regular_definitions) {
//     generate(regular_definitions);  // This function is still not implemented
// }

// Static function to construct an example NFA
// NFA NFA::construct_example_nfa() {
//
//     return nfa;
// }

// You can implement the 'generate' function if you plan to use regular definitions
// void NFA::generate(vector<string> regular_definitions) {
//     // You can parse the regular_definitions to generate NFA states and transitions
//     // This function needs to be filled based on the expected NFA generation logic
// }

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

set<char> NFA::get_transition_chars(set<Node *> nodes) {
    //TODO: implement this, this is mocked
    set<char> sett = {'a', 'b'};
    return sett;
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
