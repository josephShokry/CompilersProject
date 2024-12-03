#include "../DFA/DFA.h"
#include "../Node/Node.h"
#include <bits/stdc++.h>

using namespace std;
DFA::DFA(NFA nfa) {
    int id = 0;
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
        for (char ch : nfa.get_transition_chars(cur)) {
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

void DFA::update_mapp(map<vector<int>, int>& mapp, vector<vector<int>>& sets) {
    mapp.clear();
    for (int i=0;i<sets.size();i++) {
        mapp[sets[i]] = i;
    }
}
void DFA::minimize() {
    vector<vector<int>> sets = split_ids();
    map<vector<int>, int> mapp;
    update_mapp(mapp, sets);
    for (int i = 0;i<sets.size();i++) {
        vector<vector<int>> out = split(sets[i], mapp);
        if (out.size() == 1)continue;
        // mapp.erase(sets[i]);
        sets[i] = out[0];
        // mapp[sets[i]] = i;
        for (int j = 1;j<out.size();j++) {
            sets.push_back(out[j]);
        //     mapp[out[j]] = sets.size() - 1;
        }

        update_mapp(mapp, sets);
        i = -1;
    }
    // update the attributes of DFA
    map<int, map<char, int>> vis;
    for (int i= 0;i<sets.size();i++) {
        vector<int> v = sets[i];
        for (auto& state_entry : transition_table) {
            for (auto& map_entry: state_entry.second) {
                if (find(v.begin(), v.end(), map_entry.second) != v.end() && !vis[state_entry.first][map_entry.first]) {
                    map_entry.second = i;
                    vis[state_entry.first][map_entry.first] = 1;
                }
            }
        }
    }
    map<int, map<char, int>> new_transition_table;
    for (auto it: transition_table) {
        for (int i = 0;i<sets.size();i++) {
            vector<int> v = sets[i];
            if (find(v.begin(), v.end(), it.first) != v.end()) {
                new_transition_table[i] = it.second;
            }
        }
    }
    transition_table = new_transition_table;
    // for memory optimization do the same for other attributes
}

vector<vector<int>> DFA::split(vector<int> elems, map<vector<int>, int> mapp) {
    vector<vector<int>> out;
    vector<char> chars = {'a','b','c'};
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

vector<vector<int>> DFA::split_ids() {
    vector<vector<int>> ids(2);
    for (const auto& [node_set, id] : state_to_id) {
        bool accepting = false;
        for (Node* node: node_set) {
            if (node->get_is_accepting()) {
                ids[1].push_back(id);
                accepting = true;
                break;
            }
        }
        if (!accepting) {
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

        cout << "State " << state_id << " transitions:" << endl;

        // Iterate over each character transition for the state
        for (const auto& transition : transitions) {
            char input_char = transition.first;
            int next_state = transition.second;
            cout << "  On input '" << input_char << "' -> State " << next_state << endl;
        }
    }
}

int DFA::getStartingStateId() {
    return starting_id;

}
int DFA::getNextNodeId(int node_id, char transition_char) {
    if (transition_table[node_id].find(transition_char) == transition_table[node_id].end()) return -1;
    set<Node*> next_nodes = id_to_state[transition_table[node_id][transition_char]];
    return state_to_id[next_nodes];
}
bool DFA::isAcceptingState(int node_id) {
    set<Node*> nodes = id_to_state[node_id];
    for (auto node : nodes) {
        if (node->get_is_accepting()) {
            return true;
        }
    }
    return false;
}

