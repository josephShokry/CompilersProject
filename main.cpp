#include <fstream>
#include <iostream>

// #include "src/LexicalAnalyser/LexicalAnalyser.h"
#include "src/Utils/utils.h"

using namespace std;

int main() {
    // string rules_file_path = "testFiles/rules.txt";
    // string code_file_path = "testFiles/codeExample.txt";
    //
    // lexical_analyser* analyser = new lexical_analyser(rules_file_path, code_file_path);
    //
    // // while (analyser->has_next()) {
    // //     cout<<analyser->get_next_token()<<endl;
    // // }
    //
    // return 0;
    string test = "zz(y-z?a-f)";
    string result = utils::resolve_range(test);
    cout<<result<<"\n";
}