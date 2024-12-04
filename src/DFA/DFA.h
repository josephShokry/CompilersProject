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
    vector<char> chars;
    map<int,set<Node*>> id_to_state;
    map<set<Node*>, int> state_to_id;
    map<int,map<char,int>> transition_table;

    int get_id_from_node(Node* node);

    set<Node*> get_Nodes_from_id(int id);

    vector<vector<int>> split_ids();
    vector<vector<int>> split(vector<int> elems, map<vector<int>, int>);
    int int_to_vec_int(int x, map<vector<int>, int> &mapp);

    void update_mapp(map<vector<int>, int> &mapp, vector<vector<int>> &partitionedStates);

    void regenerateMappings();

    int get_next_node_id(int node_id, char transition_char);
    set<Node*> getNextNodes(Node* current_node, char transition_char);

public:
    DFA(NFA nfa, NFA_builder nfa_builder);

    set<Node *> getNewState(vector<int> partitionedStates);

    void minimize();
    void print_transition_table();

    Node* get_start_node() {
        return *id_to_state[starting_id].begin();
    }
    int get_starting_state_id();
    int getNextNodeId(int node_id, char transition_char);
    bool isAcceptingState(int node_id);

};



#endif //DFA_H
