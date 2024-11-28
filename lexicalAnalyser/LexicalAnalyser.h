// LexicalAnalyser.h
#ifndef LEXICAL_ANALYSER_H
#define LEXICAL_ANALYSER_H

#include <string>
using namespace std;

class LexicalAnalyser {
private:
    // Reads the contents of a file (returns NULL for now, to be implemented)
    string readFile();

    // Constructs a single start NFA from the rules (to be implemented)
    void rulesTo_NFA();

    // Converts the NFA to a DFA (to be implemented)
    void NFA_To_DFA();

    // Minimizes the DFA (to be implemented)
    void minimize_DFA();

public:
    // Parses the rules of the language from a specified file path
    void parseRules(string rulesFilePath);

    // Parses the code to be analyzed, using the previously set rules file path
    void parseCode(string rulesFilePath);

    // Retrieves the next token (currently returns NULL)
    string getNextToken();

    // Check if the lexical analyser can get more token or no
    bool hasNext();
};

#endif // LEXICAL_ANALYSER_H
