
// #include "LexicalAnalyser.h"

#include <string>

using namespace std;

class LexicalAnalyser {

private:
    string readFile() {
        return NULL;
    }

    // construct a single start NFA from the rules
    void rulesTo_NFA() {

    }

    // construct a DFA out of NFA
    void NFA_To_DFA() {

    }

    // minimize the DFA
    void minimize_DFA() {

    }

public:

    // to set the rules of the language
    void parseRules(string rulesFilePath) {

    }

    // to set the code that being analyzed against the ruled added previously
    void parseCode(string rulesFilePath) {

    }

    // to get the next token
    string getNextToken() {
        return NULL;
    }

    // Check if the lexical analyser can get more token or no
    bool hasNext() {

    }
};
