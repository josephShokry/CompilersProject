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
    map<char, vector<Node*>> neighbours;
    vector<string> tokens;

public:
    Node(int id, bool is_start = false, bool is_accepting = false)
        : id(id), is_start(is_start), is_accepting(is_accepting) {}

    int id1() const {
        return id;
    }

    bool is_start1() const {
        return is_start;
    }

    bool is_accepting1() const {
        return is_accepting;
    }

    map<char, vector<Node*>> neighbours1() const {
        return neighbours;
    }

    void add_neighbour(char transition, Node* node) {
        neighbours[transition].push_back(node);
    }

    vector<string> tokens1() const {
        return tokens;
    }

    bool has_transition(char ch) {
        return neighbours.contains(ch);
    }

    vector<Node*> get_neighbour(char ch) {
        return neighbours[ch];
    }

    // Add operator< for std::set compatibility
    bool operator<(const Node& other) const {
        return id < other.id; // Compare based on id
    }
};
