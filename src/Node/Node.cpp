//
// Created by lenovo on 11/28/2024.
//

// #include "Node.h"
#include <bits/stdc++.h>

using namespace std;

class Node {
private:
    int id;
    bool is_start;
    bool is_accepting;
    map<char, Node> neighbours;
    // add them sorted depending on the priority
    vector<string> tokens;
public:
    Node(int id, bool is_start, bool is_accepting,
        const map<char, Node> &neighbours, const vector<string> &tokens)
        : id(id),
          is_start(is_start),
          is_accepting(is_accepting),
          neighbours(neighbours),
          tokens(tokens) {
    }

    int id1() const {
        return id;
    }

    bool is_start1() const {
        return is_start;
    }

    bool is_accepting1() const {
        return is_accepting;
    }

    map<char, Node> neighbours1() const {
        return neighbours;
    }

    vector<string> tokens1() const {
        return tokens;
    }
};