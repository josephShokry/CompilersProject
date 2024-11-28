// node.h
#ifndef NODE_H
#define NODE_H

#include <map>
#include <vector>
#include <string>

using namespace std;

class Node {
private:
    int id;
    bool is_start;
    bool is_accepting;
    map<char, Node> neighbours; // Maps characters to corresponding neighboring nodes
    vector<string> tokens; // Stores the tokens associated with this node

public:
    // Constructor to initialize the Node
    Node(int id, bool is_start, bool is_accepting,
         const map<char, Node> &neighbours, const vector<string> &tokens)
        : id(id),
          is_start(is_start),
          is_accepting(is_accepting),
          neighbours(neighbours),
          tokens(tokens) {
    }

    // Getter for id
    int id1() const {
        return id;
    }

    // Getter for is_start flag
    bool is_start1() const {
        return is_start;
    }

    // Getter for is_accepting flag
    bool is_accepting1() const {
        return is_accepting;
    }

    // Getter for neighbours map
    map<char, Node> neighbours1() const {
        return neighbours;
    }

    // Getter for tokens vector
    vector<string> tokens1() const {
        return tokens;
    }
};

#endif // NODE_H
