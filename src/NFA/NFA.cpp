// NFA.cpp
#include "NFA.h"

#include <vector>
#include <bits/stdc++.h>
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
set<char> NFA::get_transition_chars(set<Node *> nodes) {
    //TODO: implement this, this is mocked
    set<char> sett = {'a','b','c'};
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
