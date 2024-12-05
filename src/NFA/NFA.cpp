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

vector<char> NFA::get_transition_chars() {
    unordered_set<int> visited;
    queue<Node*> q;
    q.push(get_start_node());
    visited.insert(get_start_node()->get_id());
    set<char>transitions_set;
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        for (const auto& [symbol, neighbours] : current->get_neighbours()) {
            transitions_set.insert(symbol);
            for (Node* neighbour : neighbours) {
                if (!visited.contains(neighbour->get_id())) {
                    visited.insert(neighbour->get_id());
                    q.push(neighbour);
                }
            }
        }
    }
    transitions_set.erase('$');
    return {transitions_set.begin(), transitions_set.end()};
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
