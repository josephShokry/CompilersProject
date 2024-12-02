//
// Node.h
// Created by lenovo on 11/28/2024.
//

#ifndef NODE_H
#define NODE_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class Node {
private:
    int id; // Unique identifier for the node
    bool is_start; // True if this is the start state
    bool is_accepting; // True if this is an accepting state
    // TODO check if it causes a problem
    map<char, vector<Node*>> neighbours; // Transitions: char -> list of target nodes

private:
    vector<string> tokens; // Additional information or tokens associated with the node

public:
    // Constructor
    Node(int id, bool is_start = false, bool is_accepting = false)
        : id(id), is_start(is_start), is_accepting(is_accepting) {}

    // Get the node's ID
    int get_id() const {
        return id;
    }

    // Check if this node is the start state
    bool get_is_start() const {
        return is_start;
    }

    // Check if this node is an accepting state
    bool get_is_accepting() const {
        return is_accepting;
    }

    // Get the node's transitions
    map<char, vector<Node*>> get_neighbours() const {
        return neighbours;
    }

    void concatenate_neighbours(map<char, vector<Node*>> neighbours) {
        for (const auto& [key, vec] : neighbours) {
            this->neighbours[key].insert(this->neighbours[key].end(), vec.begin(), vec.end());
        }
    }

    // Add a neighbor node for a given transition character
    void add_neighbour(char transition, Node* node) {
        neighbours[transition].push_back(node);
    }

    bool has_transition(char ch) {
        return neighbours.contains(ch);
    }

    vector<Node*> get_neighbour(char ch) {
        return neighbours[ch];
    }

    // Add a token to the node
    void add_token(const string& token) {
        tokens.push_back(token);
    }

    // Get the node's tokens
    vector<string> get_tokens() const {
        return tokens;
    }
    void set_is_start(bool is_start) {
        this->is_start = is_start;
    }
    void set_is_accepting(bool is_accepting) {
        this->is_accepting = is_accepting;
    }

    void set_id(int id) {
        this->id = id;
    }

    // Operator< for use in std::set (compares nodes by their IDs)
    bool operator<(const Node& other) const {
        return id < other.id;
    }

};

#endif // NODE_H