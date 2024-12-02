//
// Created by alsay on 11/28/2024.
//

#include "utils.h"
#include <bits/stdc++.h>
using namespace std;

string utils::resolve_range(string regex) {
    string after_resolving;
    for (int i = 0 ; i < regex.size() ; i++) {
        if (regex[i] == '-' && regex[i-1] != '\\') {
            after_resolving.pop_back();
            for (char j = regex[i-1] ; j <= regex[i+1] ; j++) {
                after_resolving += j + string(1, '|');
            }
            after_resolving.pop_back();
            i++;
        }
        else{
            after_resolving += regex[i];
        }
    }
    return after_resolving;
}


string utils::remove_spaces_from_regex(string regex) {
    string result;
    for (char c : regex) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}
