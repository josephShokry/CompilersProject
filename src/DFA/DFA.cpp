#include "dfa.h"

DFA::DFA(NFA nfa) {
    int id = 0;
    queue<set<Node>> q;
    set<Node*> sett;
    sett.insert(nfa.start_node1());
    sett.insert(nfa.get_equivilant_nodes(nfa.start_node1()));
    q.push(sett);
    id_to_state[id] = sett;
    state_to_id[sett] = id++;
    while (!q.empty()) {
        set<Node*> cur = q.front();
        int cur_id = state_to_id[cur];
        q.pop();
        for (char ch : nfa.get_transition_chars(cur)) {
            set<Node*> nei = nfa.get_next_nodes(cur, ch);
            if (state_to_id.contains(nei)) {
                transition_table[cur_id][ch] = state_to_id[nei];
                continue;
            }
            q.push(nei);
            id_to_state[id] = nei;
            state_to_id[nei] = id++;
        }
    }
}

void DFA::minimize() {
    vector<vector<int>> sets = split_ids();
    map<vector<int>, int> mapp;
    mapp[sets[0]] = 0;
    mapp[sets[1]] = 1;
    for (int i = 0;i<sets.size();i++) {
        vector<vector<int>> out = split(sets[i], mapp);
        if (out.size() == 1)continue;
        mapp.erase(sets[i]);
        sets[i] = out[0];
        mapp[sets[i]] = i;
        for (int j = 1;j<out.size();j++) {
            sets.push_back(out[j]);
            mapp[out[j]] = sets.size() - 1;
        }
        i = -1;
    }
    // update the attributes of DFA
}

vector<vector<int>> DFA::split(vector<int> elems, map<vector<int>, int> mapp) {
    vector<vector<int>> out;

    return out;
}

set<Node> DFA::getNextNodes(const Node &current_node, char transition_char) {
    int current_id = get_id_from_node(current_node);
    set<Node> next_nodes = id_to_state[transition_table[current_id][transition_char]];
    return next_nodes;
}

int DFA::get_id_from_node(const Node& node) const {
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
        bool acctepting = false;
        for (Node node: node_set) {
            if (node.is_accepting1()) {
                ids[0].push_back(id);
                acctepting = true;
                break;
            }
        }
        if (!acctepting) {
            ids[1].push_back(id);
        }
    }
    return ids;
}
