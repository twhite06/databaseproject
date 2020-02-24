 * stringProcessing.cpp
 * Author: Tim White 
 * Date: 11/15/2019

#include "stringProcessing.h"
#include <string>
#include <cctype>
#include <iostream>

using namespace std;


string stripNonAlphaNum(string input){
    int size = input.size();
    int i = 0, first = 0, last = 0;
    while(!isalnum(input[i])){
        i++;
    }
    first = i;
    i = size - 1;
    while (!isalnum(input[i])){
        i--;
    }
    last = i;
    input = input.substr(first, (last-first) + 1);
    return input;
}
