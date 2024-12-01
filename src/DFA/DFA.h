//
// Created by lenovo on 11/28/2024.
//

#ifndef DFA_H
#define DFA_H


#include "../Node/Node.h"
#include "../NFA/NFA.h"

using namespace std;

class DFA {
private:
    int starting_id = 0;
    map<int,set<Node*>> id_to_state;
    map<set<Node*>, int> state_to_id;
    map<int,map<char,int>> transition_table;
    vector<char> chars = {'a'};

    int get_id_from_node(Node* node);
    vector<vector<int>> split_ids();


    vector<vector<int>> split(vector<int> elems, map<vector<int>, int>);

public:
    DFA(NFA nfa);
    void minimize();
    set<Node> getNextNodes(const Node &current_node, char transition_char);
    void print_transition_table();

    Node* start_node1() {
        return *id_to_state[starting_id].begin();
    }
};



#endif //DFA_H
