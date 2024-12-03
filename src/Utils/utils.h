//
// Created by alsay on 11/28/2024.
//

#ifndef UTILS_H
#define UTILS_H


#include <bits/stdc++.h>
using namespace std;

class utils {
public:
    // Maps the input
    static string get_input_key();

    static string resolve_range(string regex);

    static string remove_spaces_from_regex(string regex);
};


#endif //UTILS_H
