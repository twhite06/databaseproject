 * main.cpp
 * COMP15
 * Spring 2019
 *
 *
 * Author: Tim White 
 * Date: 11/15/2019

#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream>

#include "DirNode.h"
#include "FSTree.h"
#include "HashClass.h"
#include "stringProcessing.h"

using namespace std;

void traverseAndHash(DirNode *curr, string path, HashClass &hashInstance, 
                    int FO);
void readQuery(string outFile, HashClass &hashInstance);


int main(int args, char *argv[]) 
{
    if (args == 3){
    string directory = argv[1], outFile = argv[2];
    ofstream out;
    FSTree Tree(directory);
    HashClass Hashington;
    DirNode *root = Tree.getRoot();
    //traverse all the files and put content into the hash table
    int filesOpened = 0;   
    traverseAndHash(root, directory, Hashington, filesOpened);
    readQuery(outFile, Hashington);
    } else {
        cerr << "Usage:  gerp directory output_file" << endl;
        return 0;
    }
}

void traverseAndHash(DirNode *curr, string path, HashClass &hashInstance,
                    int FO){
    string tempPath;
    if (curr->isEmpty()){
        return;
    } 
    if (curr->hasFiles()){
        int numberFiles = curr->numFiles();
        for (int i = 0; i < numberFiles; i++){
            tempPath = path + "/" + curr->getFile(i);
            hashInstance.mainHashing(tempPath, FO);
            FO++;
            
        }
    }
    if (curr->hasSubDir()){
        int numSubDir = curr->numSubDirs();
        for (int i = 0; i < numSubDir; i++){
            DirNode *subD = curr->getSubDir(i);
            tempPath = path + "/" + subD->getName();
            traverseAndHash(subD, tempPath, hashInstance, FO);
        }
    }
}

void readQuery(string outFile, HashClass &hashInstance){
    bool quitIt = false;
    string querycommand, parsedQC, qWord = "@quit", wordInput, stringToFind;
    string iLetter = "@i", iWord = "@insensitive", qLetter = "@q", outF ="@f";
    ofstream out;
    out.open(outFile);
    while (!quitIt){
        cout << "Query?" << endl;
        getline(cin, querycommand);
        stringstream ss(querycommand);
        ss >> parsedQC;
        if ((parsedQC == iLetter) or (parsedQC == iWord)){
            ss >> wordInput;
            stringToFind = stripNonAlphaNum(wordInput);
            hashInstance.searchAndPrint(stringToFind, parsedQC, out);
        } else if (parsedQC == outF) {
            out.close();
            ss >> outFile;
            out.open(outFile);
            // Add changed outfile
        } else if ((parsedQC == qWord) or (parsedQC == qLetter)) {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            quitIt = true;
        } else {
            //check if possible to to have command not be one of the choices
            stringToFind = stripNonAlphaNum(parsedQC);
            hashInstance.searchAndPrint(stringToFind, parsedQC, out);
        }
    }
    out.close();
    return;
} 
