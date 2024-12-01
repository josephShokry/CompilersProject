// NFA.cpp
#include "NFA.h"

// Constructor for NFA, which initializes the NFA with given regular definitions
NFA::NFA(vector<string> regular_definitions) {
    generate(regular_definitions);  // This function is still not implemented
}

// Static function to construct an example NFA
NFA NFA::construct_example_nfa() {
    // Create nodes
    Node* state0 = new Node(0, true, false);  // Start state
    Node* state1 = new Node(1, false, true);
    Node* state2 = new Node(2, false, true);
    Node* state3 = new Node(3);
    Node* state4 = new Node(4, false, true);
    Node* state5 = new Node(5); // Accepting state

    // Define transitions
    state0->add_neighbour('a', state3);  // Epsilon transition to state 1
    state0->add_neighbour('b', state1);  // Epsilon transition to state 1

    state1->add_neighbour('a', state2);  // Epsilon transition to state 1
    state1->add_neighbour('b', state5);  // Epsilon transition to state 1

    state2->add_neighbour('a', state2);  // Epsilon transition to state 1
    state2->add_neighbour('b', state5);  // Epsilon transition to state 1

    state3->add_neighbour('a', state0);  // Epsilon transition to state 1
    state3->add_neighbour('b', state4);  // Epsilon transition to state 1

    state4->add_neighbour('a', state2);  // Epsilon transition to state 1
    state4->add_neighbour('b', state5);  // Epsilon transition to state 1

    state5->add_neighbour('a', state5);  // Epsilon transition to state 1
    state5->add_neighbour('b', state5);  // Epsilon transition to state 1


    // Build NFA
    NFA nfa({});
    nfa.start_node = state0;
    nfa.end_node = state5;  // The final state

    return nfa;

    return nfa;
}

// You can implement the 'generate' function if you plan to use regular definitions
void NFA::generate(vector<string> regular_definitions) {
    // You can parse the regular_definitions to generate NFA states and transitions
    // This function needs to be filled based on the expected NFA generation logic
}

set<Node*> NFA::get_equivilant_nodes(set<Node*> current_nodes) {
    set<Node*> next = current_nodes;
    int size = next.size();
    while (true) {
        set<Node*> s = get_next_nodes(next, eps);
        next.insert(s.begin(), s.end());
        if (next.size() == size)break;
        size = next.size();
    }

    return next;
}

set<char> NFA::get_transition_chars(set<Node*> nodes) {
    //TODO: implement this, this is mocked
    set<char> sett = {'a','b'};
    return sett;
}

set<Node*> NFA::get_next_nodes(set<Node*> current_nodes, char transition) {
    set<Node*> sett;

    for (Node* node: current_nodes) {
        if (node->has_transition(transition)) {
            vector<Node*> nei = node->get_neighbour(transition);
            sett.insert(nei.begin(), nei.end());
        }
    }
    return sett;
}

// // Concatenate two NFAs: NFA_1 followed by NFA_2
// NFA NFA::concatintate(NFA NFA_1, NFA NFA_2) {
//
// }
//
// // Join two NFAs: Create a new start state that has epsilon transitions to the start state of both NFA_1 and NFA_2
// NFA NFA::join(NFA NFA_1, NFA NFA_2) {
//
// }
//
// // Apply Kleene closure to an NFA: Create a new start state with an epsilon transition to the original start state
// // and a new accepting state with epsilon transitions to the original accepting state and back to the start state
// NFA NFA::kleene_clouser(NFA NFA_1, NFA NFA_2) {
//
// }
