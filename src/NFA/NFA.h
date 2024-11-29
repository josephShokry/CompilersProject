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
    Node* start_node = nullptr;
    Node* end_node = nullptr;

    void generate(vector<string> regular_definitions);

    NFA concatintate(NFA NFA_1, NFA NFA_2);

    NFA join(NFA NFA_1, NFA NFA_2);

    NFA kleene_clouser(NFA NFA_1, NFA NFA_2);


public:
    NFA(vector<string> regular_definitions);

    Node * start_node1() const {
        return start_node;
    }

    // return the set of node that will be in case of getting the char
    set<Node*> get_next_nodes(Node current_node, char transition);
    // return the set of node that has eps transitions
    set<Node*> get_equivilant_nodes(set<Node> current_node);
    set<char> get_transition_chars(set<Node> nodes);

};



#endif //NFA_H
