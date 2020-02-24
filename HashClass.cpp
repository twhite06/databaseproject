 * HashClass.cpp
 * COMP15
 * Spring 2019
 *
 *
 * Author: Tim White 
 * Date: 11/15/2019

#include "HashClass.h"

#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

HashClass:: HashClass(){
    // Constructor to intitialize the hash table
    wordsStored = 0;
    // dynamic array size
    capacity = 10;
    data = new vector<bucketData>[capacity];
    for (int i = 0; i < 10; i++){
    }
}

void HashClass:: mainHashing(string path, int filesOpened){
    ifstream input;
    //counter to keep track of what linenumber is currently being visited
    int linenumber = 0;
    input.open(path);
    if (!input.is_open()){
        cerr << "File could not be opened";
        return;
    }
    filesOpened++;
    // Add the file path to the vector of file paths
    paths.push_back(path);
    string tempAux;
    
    // Read file
    while(getline(input, tempAux)){
        linenumber++;
        // Struct used to add the content of a line
        lineContent LC;
        LC.line = tempAux;
        LC.lineNum = linenumber;
        lineStuff.push_back(LC);
        stringstream ss(LC.line);
        string qWord;
        while(ss >> qWord){
            wordContent WC;
            WC.word = qWord;
        // index of the info for "line" and "path" used for quick access
            int lineIndex = lineStuff.size() - 1;
            int pathIndex = paths.size() - 1;
            Indexes currIndexes = {lineIndex, pathIndex};
            WC.LPInfo.push_back(currIndexes);
        // case for needing to expand
            if ((wordsStored / capacity) > .75){
                expand();
                hashAndPush(WC, currIndexes);

            }
        // no expand case
            else {
                hashAndPush(WC, currIndexes);
            }
            wordsStored++;
       }
    }
    input.close();
}

void HashClass:: expand(){
    int newcapacity = capacity * 1.97;
    vector<bucketData> *newData = new vector<bucketData>[newcapacity];
    for (int i = 0; i < capacity; i++){
        for (size_t j = 0; j < data[i].size(); j++){
            size_t slt = hash<string>{}(string(data[i][j].lowCaseWord)) % newcapacity;
            newData[slt].push_back(data[i][j]);
        }
    }
    capacity = newcapacity;
    delete []data;
    data = newData;
}

void HashClass:: hashAndPush(wordContent WC, Indexes currIndexes){
    string wordToHash = WC.word;
    for (size_t i = 0; i < wordToHash.length(); i++){
        wordToHash[i] = tolower(wordToHash[i]);
    }
    size_t bucket = hash<string>{}(string(wordToHash)) % capacity;
    bucketData BData;
    BData.lowCaseWord = wordToHash;
    BData.WCVec.push_back(WC);
    // before pushing back check to see if the word already exists
    // in the index. If it does push indexes into LP struct
    bool wordInstanceAdded = false;
    for (size_t i = 0; i < data[bucket].size(); i++){
        // Check for case of exact match of word at an index 
        for (size_t j = 0; j < data[bucket][i].WCVec.size(); j++){
            if (data[bucket][i].WCVec[j].word == WC.word){
                data[bucket][i].WCVec[j].LPInfo.push_back(currIndexes);
                wordInstanceAdded = true;
                break;
            }
        }

        // Case of uppercase version of word
        if (data[bucket][i].lowCaseWord == wordToHash){
            bool wordExists = false;
            for (size_t j = 0; j < data[bucket][i].WCVec.size(); j++){
                if (data[bucket][i].WCVec[j].word == WC.word){
                    data[bucket][i].WCVec[j].LPInfo.push_back(currIndexes);
                        wordInstanceAdded = true;
                        wordExists = true;
                        break;
                }
            }
            if (!wordExists){
                data[bucket][i].WCVec.push_back(WC);
                wordInstanceAdded = true;
                break;
            }
        }
    }

    // Case of brand new word at same index as another
    if (!wordInstanceAdded){
        data[bucket].push_back(BData);
    }
}

void HashClass:: searchAndPrint(string wordToSearch, string command, 
                                ostream &out){
    string loweredWord = wordToSearch, iLetter = "@i", iWord = "@insensitive"; 
    for (size_t i = 0; i < loweredWord.length(); i++){
        loweredWord[i] = tolower(loweredWord[i]);
    }
    size_t bucket = hash<string>{}(string(loweredWord)) % capacity;
    // if the command is case insensetive, call insensitive function.
    // else call the case sensitive function

    // Case insensitive
    if ((command == iLetter) or (command == iWord)){
        searchPrintInsensitive(bucket, loweredWord, out);
    // Case sensitive
    } else {
        searchPrintSensitive(bucket, wordToSearch, loweredWord, out);    
    }
}


void HashClass:: searchPrintSensitive(int bucket, string wordToSearch,
                                      string lowWord, ostream &out){
    for (size_t i = 0; i < data[bucket].size(); i++){
        if (data[bucket][i].lowCaseWord == lowWord){
            int indexForPath, indexForLine;
            for (size_t j =0; j < data[bucket][i].WCVec.size(); j++){
                if (data[bucket][i].WCVec[j].word == wordToSearch){
                    for (size_t k = 0; k < data[bucket][i].WCVec[j].LPInfo.size(); k++){
                        indexForPath = data[bucket][i].WCVec[j].LPInfo[k].path;
                        indexForLine = data[bucket][i].WCVec[j].LPInfo[k].line;
                        out << paths[indexForPath] << ":";
                        out << lineStuff[indexForLine].lineNum << ": ";
                        out << lineStuff[indexForLine].line << endl; 
                    }   
                }
            }
        }
    }
}

void HashClass:: searchPrintInsensitive(int bucket, string wordToSearch, 
                                        ostream &out){
    for (size_t i = 0; i < data[bucket].size(); i++){
        if (data[bucket][i].lowCaseWord == wordToSearch){
            int indexForPath, indexForLine;
            for (size_t j =0; j < data[bucket][i].WCVec.size(); j++){
                    for (size_t k = 0; k < data[bucket][i].WCVec[j].LPInfo.size(); k++){
                        indexForPath = data[bucket][i].WCVec[j].LPInfo[k].path;
                        indexForLine = data[bucket][i].WCVec[j].LPInfo[k].line;
                        out << paths[indexForPath] << ":";
                        out << lineStuff[indexForLine].lineNum << ": ";
                        out << lineStuff[indexForLine].line << endl; 
                    }   
            }
        }
    }
}
