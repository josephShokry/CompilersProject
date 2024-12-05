#include "../DFA/DFA.h"
#include "../Node/Node.h"
#include "../NFA/NFA_builder.h"
#include <bits/stdc++.h>

using namespace std;
DFA::DFA(NFA nfa, NFA_builder nfa_builder) {
    int id = 0;
    chars = nfa.get_transition_chars(nfa_builder);
    token_to_priority = nfa_builder.get_priority();
    queue<set<Node*>> q;
    set<Node*> sett;
    sett.insert(nfa.get_start_node());
    set<Node*> eq = nfa.get_equivilant_nodes(sett);
    sett.insert(eq.begin(), eq.end());
    q.push(sett);
    id_to_state[id] = sett;
    state_to_id[sett] = id++;
    while (!q.empty()) {
        set<Node*> cur = q.front();
        int cur_id = state_to_id[cur];
        q.pop();
        for (char& ch : nfa.get_transition_chars(nfa_builder)) {
            set<Node*> nei = nfa.get_next_nodes(cur, ch);
            set<Node*> eq = nfa.get_equivilant_nodes(nei);
            nei.insert(eq.begin(), eq.end());
            if (state_to_id.contains(nei)) {
                transition_table[cur_id][ch] = state_to_id[nei];
                continue;
            }
            if (nei.empty()) continue;

            q.push(nei);
            id_to_state[id] = nei;
            state_to_id[nei] = id++;
            transition_table[cur_id][ch] = state_to_id[nei];
        }
    }
}

set<Node *> DFA::getNewState(vector<int> partitionedStates) {
    set<Node*> sett;
    for (int i:partitionedStates) {
        set<Node*> old = id_to_state[i];
        sett.insert(old.begin(), old.end());
    }
    return sett;
}

void DFA::update_mapp(map<vector<int>, int>& stateGroupMapping, vector<vector<int>>& partitionedStates) {
    // Remove empty partitions
    partitionedStates.erase(
        remove_if(partitionedStates.begin(), partitionedStates.end(),
                  [](const vector<int>& state) { return state.empty(); }),
        partitionedStates.end()
    );
    stateGroupMapping.clear();
    for (int i=0;i<partitionedStates.size();i++) {
        stateGroupMapping[partitionedStates[i]] = i;
    }
}

void DFA::minimize() {
    vector<vector<int>> partitionedStates = split_ids();
    map<vector<int>, int> stateGroupMapping;
    update_mapp(stateGroupMapping, partitionedStates);

    for (int partitionIndex = 0; partitionIndex < partitionedStates.size(); partitionIndex++) {
        vector<vector<int>> splitPartitions = split(partitionedStates[partitionIndex], stateGroupMapping);
        if (splitPartitions.size() == 1) continue;

        partitionedStates[partitionIndex] = splitPartitions[0];
        for (int splitIndex = 1; splitIndex < splitPartitions.size(); splitIndex++) {
            partitionedStates.push_back(splitPartitions[splitIndex]);
        }

        update_mapp(stateGroupMapping, partitionedStates);
        partitionIndex = -1;
    }

    // Update the attributes of the DFA
    map<int, map<char, int>> visitedTransitions;
    for (int groupIndex = 0; groupIndex < partitionedStates.size(); groupIndex++) {
        vector<int> currentGroup = partitionedStates[groupIndex];
        for (auto& stateEntry : transition_table) {
            for (auto& transition : stateEntry.second) {
                if (find(currentGroup.begin(), currentGroup.end(), transition.second) != currentGroup.end() &&
                    !visitedTransitions[stateEntry.first][transition.first]) {
                    transition.second = groupIndex;
                    visitedTransitions[stateEntry.first][transition.first] = 1;
                }
            }
        }
    }

    map<int, map<char, int>> updatedTransitionTable;
    for (auto& stateEntry : transition_table) {
        for (int groupIndex = 0; groupIndex < partitionedStates.size(); groupIndex++) {
            vector<int> currentGroup = partitionedStates[groupIndex];
            if (find(currentGroup.begin(), currentGroup.end(), stateEntry.first) != currentGroup.end()) {
                updatedTransitionTable[groupIndex] = stateEntry.second;
            }
        }
    }
    transition_table = updatedTransitionTable;
    //update mapps
    map<int, set<Node*>> new_id_to_state;
    map<set<Node*>, int> new_state_to_id;
    for (int i = 0;i<partitionedStates.size();i++) {
        set<Node*> eq;
        for (int state: partitionedStates[i]) {
            set<Node*> old = id_to_state[state];
            eq.insert(old.begin(), old.end());
        }
        new_id_to_state[i] = eq;
        new_state_to_id[eq] = i;
    }
    id_to_state = new_id_to_state;
    state_to_id = new_state_to_id;

    //Find the new starting state ID
    for (auto& it: state_to_id) {
        for (Node* node: it.first) {
            if (node->get_is_start()) {
                starting_id = it.second;
                return;
            }
        }
    }
}

vector<vector<int>> DFA::split(vector<int> elems, map<vector<int>, int> mapp) {
    vector<vector<int>> out;
    map<vector<int>, vector<int>> m;
    for (int i = 0;i<elems.size();i++) {
        vector<int> nexts(chars.size(), -1);
        for (int j = 0;j<chars.size();j++) {
            nexts[j] = int_to_vec_int(get_next_node_id(elems[i], chars[j]), mapp);
        }
        m[nexts].push_back(elems[i]);
    }
    for (auto it:m) {
        out.push_back(it.second);
    }
    return out;
}

int DFA::int_to_vec_int(int x, map<vector<int>, int>& mapp) {
    for (auto& it: mapp) {
        if (find(it.first.begin(), it.first.end(), x) != it.first.end()) {
            return it.second;
        }
    }
    return -1;
}

int DFA::get_next_node_id(int node_id, char transition_char) {
    if (transition_table[node_id].contains(transition_char))
        return transition_table[node_id][transition_char];
    return -1;
}

set<Node*> DFA::getNextNodes(Node* current_node, char transition_char) {
    int current_id = get_id_from_node(current_node);
    set<Node*> next_nodes = id_to_state[transition_table[current_id][transition_char]];
    return next_nodes;
}

int DFA::get_id_from_node(Node* node) {
    for (const auto& [node_set, id] : state_to_id) {
        if (node_set.contains(node)) {
            return id;
        }
    }
    return -1;
}

set<Node*> DFA::get_Nodes_from_id(int id) {
    return id_to_state[id];
}

vector<vector<int>> DFA::split_ids() {
    vector<vector<int>> ids(1);
    map<string, int> accepting_index;
    for (const auto& [node_set, id] : state_to_id) {
        bool accepting = false;
        for (Node* node: node_set) {
            if (node->get_is_accepting()) {
                accepting = true;
                break;
            }
        }
        if (accepting) {
            string token = get_high_priority_token(id);
            if (!accepting_index.contains(token)) {
                ids.push_back({id});
                accepting_index[token] = ids.size()-1;
            }
            else {
                ids[accepting_index[token]].push_back(id);
            }
        }
        else {
            ids[0].push_back(id);
        }
    }
    return ids;
}

void DFA::print_transition_table() {
    cout << "Transition Table:" << endl;

    // Iterate over each state in the transition table
    for (const auto& state_entry : transition_table) {
        int state_id = state_entry.first;
        const map<char, int>& transitions = state_entry.second;

        bool accepting = isAcceptingState(state_id);
        cout << "State " << state_id << " transitions "<< (accepting?"(Accepting)":"(Not Accepting)")<< " :" << endl;

        // Iterate over each character transition for the state
        for (const auto& transition : transitions) {
            char input_char = transition.first;
            int next_state = transition.second;
            cout << "  On input '" << input_char << "' -> State " << next_state << endl;
        }
    }
}

int DFA::get_starting_state_id() {
    return starting_id;
}

int DFA::getNextNodeId(int node_id, char transition_char) {
    if (transition_table[node_id].find(transition_char) == transition_table[node_id].end()) return -1;
    set<Node*> next_nodes = id_to_state[transition_table[node_id][transition_char]];
    return state_to_id[next_nodes];
}

bool DFA::isAcceptingState(int node_id) {
    set<Node*> nodes = get_Nodes_from_id(node_id);
    for (auto node : nodes) {
        if (node->get_is_accepting()) {
            return true;
        }
    }
    return false;
}

string DFA::get_high_priority_token(int node_id) {
    string high_priority_token ;
    int min_value = 22;
    set<Node*> nodes = get_Nodes_from_id(node_id);
    for (auto node : nodes) {
        if (!node->get_is_accepting())continue;
        for (auto tokens :node->get_tokens()) {
            if (token_to_priority[tokens] < min_value) {
                min_value = token_to_priority[tokens];
                high_priority_token = tokens;
            }
        }
    }
    return high_priority_token;
}
