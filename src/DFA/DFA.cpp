#include "../DFA/DFA.h"
#include "../Node/Node.h"
#include <bits/stdc++.h>

using namespace std;
void DFA::minimize() {
    // Placeholder for DFA minimization logic
}

set<Node> getNextNode(const Node &current_node, char transition_char){
    set<Node> next_nodes;
    // Placeholder for logic to get the next nodes
    return next_nodes;
}
int DFA::getStartingStateId() {
    return starting_id;

}
int DFA::getNextNodeId(int node_id, char transition_char) {
    if (transition_table[node_id].find(transition_char) == transition_table[node_id].end()) return -1;
    set<Node> next_nodes = id_to_state[transition_table[node_id][transition_char]];
    return state_to_id[next_nodes];
}
bool DFA::isAcceptingState(int node_id) {
    set<Node> nodes = id_to_state[node_id];
    for (auto node : nodes) {
        if (node.is_accepting1()) {
            return true;
        }
    }
    return false;
}


