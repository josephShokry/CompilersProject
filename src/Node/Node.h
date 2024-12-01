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
    map<char, vector<Node*>> neighbours; // Transitions: char -> list of target nodes
    vector<string> tokens; // Additional information or tokens associated with the node

public:
    // Constructor
    Node(int id, bool is_start = false, bool is_accepting = false)
        : id(id), is_start(is_start), is_accepting(is_accepting) {}

    // Get the node's ID
    int id1() const {
        return id;
    }

    // Check if this node is the start state
    bool is_start1() const {
        return is_start;
    }

    // Check if this node is an accepting state
    bool is_accepting1() const {
        return is_accepting;
    }

    // Get the node's transitions
    map<char, vector<Node*>> neighbours1() const {
        return neighbours;
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
    vector<string> tokens1() const {
        return tokens;
    }

    // Operator< for use in std::set (compares nodes by their IDs)
    bool operator<(const Node& other) const {
        return id < other.id;
    }
};

#endif // NODE_H
