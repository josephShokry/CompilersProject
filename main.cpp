#include <fstream>
#include <iostream>

// #include "LexicalAnalyser/LexicalAnalyser.h"
#include "src/DFA/DFA.h"
#include "src/NFA/NFA.h"


using namespace std;

int main() {
    string rules_file_path = "testFiles/rules.txt";
    string code_file_path = "testFiles/codeExample.txt";

    // lexical_analyser* analyser = new lexical_analyser(rules_file_path, code_file_path);
    //
    // while (analyser->has_next()) {
    //     cout<<analyser->get_next_token()<<endl;
    // }

    NFA nfa = NFA::construct_example_nfa();

    DFA dfa(nfa);  // This calls the DFA constructor that takes an NFA as an argument

    // Optionally, print out or verify the DFA contents here
    // For example, printing the start state of the DFA
    dfa.print_transition_table();
    cout<<"###############33"<<endl;
    dfa.minimize();
    dfa.print_transition_table();


    return 0;
}