//
// Created by lenovo on 11/28/2024.
//

#ifndef NFA_H
#define NFA_H
#include <vector>
#include <bits/stdc++.h>
#include "../Node/Node.h"

using namespace std;

class NFA {
private:
    Node *start_node = nullptr;
    Node *end_node = nullptr;

public:
    char eps = '$';

    NFA() = default;

    NFA(Node *start_node, Node *end_node) : start_node(start_node), end_node(end_node) {}

    // return the set of node and its equivilants that will be in case of getting the char
    set<Node *> get_next_nodes(set<Node *> current_nodes, char transition);

    // return the set of node that has eps transitions
    set<Node *> get_equivilant_nodes(set<Node *> current_nodes);

    set<char> get_transition_chars(set<Node *> nodes);

    static NFA construct_example_nfa();

    Node *get_start_node();

    void set_start_node(Node *start_node);

    Node *get_end_node();

    void set_end_node(Node *end_node);


    // Node * start_node1() const {
    //     return start_node;
    // }
};


#endif //NFA_H
