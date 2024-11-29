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

    void generate(vector<string> regular_definitions);

    NFA concatintate(NFA NFA_1, NFA NFA_2);

    NFA join(NFA NFA_1, NFA NFA_2);

    NFA kleene_clouser(NFA NFA_1, NFA NFA_2);

public:
    NFA(vector<string> regular_definitions);
};


#endif //NFA_H
