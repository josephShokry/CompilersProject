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
        : id(id), is_start(is_start), is_accepting(is_accepting) {
    }

    int get_id() const {
        return id;
    }

    void set_id(int id) {
        this->id = id;
    }

    void set_is_start(bool is_start) {
        this->is_start = is_start;
    }

    void set_is_accepting(bool is_accepting) {
        this->is_accepting = is_accepting;
    }

    void set_neighbours(const map<char, vector<Node *> > &neighbours) {
        this->neighbours = neighbours;
    }

    void set_tokens(const vector<string> &tokens) {
        this->tokens = tokens;
    }

    void add_token(const string token) {
        tokens.push_back(token);
    }

    bool get_is_start() const {
        return is_start;
    }

    bool get_is_accepting() const {
        return is_accepting;
    }

    map<char, vector<Node*>> get_neighbours() const {
        return neighbours;
    }

    void add_neighbour(char transition, Node* node) {
        neighbours[transition].push_back(node);
    }

    vector<string> get_tokens() const {
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
