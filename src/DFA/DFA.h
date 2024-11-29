//
// Created by lenovo on 11/28/2024.
//

#ifndef DFA_H
#define DFA_H
#include <bits/stdc++.h>



class DFA {
private:
    int starting_id;
    map<int,set<Node>> id_to_state;
    map<set<Node>, int> state_to_id;
    map<int,map<char,int>> transition_table;

public:
    void minimize();
    set<Node> getNextNodes(Node curent_node, char transition_char);
};



#endif //DFA_H
