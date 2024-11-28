#include <fstream>
#include <iostream>

#include "lexicalAnalyser/LexicalAnalyser.h"


using namespace std;

int main() {
    string rulesFilePath = "testFiles/rules.txt";
    string codeFilePath = "testFiles/codeExample.txt";

    LexicalAnalyser lexicalAnalyser;
    lexicalAnalyser.parseRules(rulesFilePath);
    lexicalAnalyser.parseCode(codeFilePath);

    while (lexicalAnalyser.hasNext()) {
        cout<<lexicalAnalyser.getNextToken()<<endl;
    }

    return 0;
}