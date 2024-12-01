//
// Created by lenovo on 11/28/2024.
//

#ifndef DFA_H
#define DFA_H

#include <bits/stdc++.h>
#include "../Node/Node.h"

using namespace std;
class DFA {
private:
    int starting_id;
    map<int,set<Node>> id_to_state;
    map<set<Node>, int> state_to_id;
    map<int,map<char,int>> transition_table;

public:
    void minimize();
    set<Node> getNextNodes(const Node &current_node, char transition_char);
    int getNextNodeId(int node_id, char transition_char);
    int getStartingStateId();
    bool isAcceptingState(int node_id);
};



#endif //DFA_H
