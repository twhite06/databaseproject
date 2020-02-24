 * FSTreeTraverse.cpp
 * COMP15
 * Spring 2019
 *
 *
 * Author: Tim White 
 * Date: 11/15/2019

// Build a tree to hold the paths to each of the files in a given directory

#include <iostream>
#include <sstream>
#include <cctype>

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
    while (!quitIt){
        cout << "Query?" << endl;
        getline(cin, querycommand);
        stringstream ss(querycommand);
        ss >> parsedQC;
        // cerr << parsedQC << endl;
        if ((parsedQC == iLetter) or (parsedQC == iWord)){
            // cerr << "inside insensitive case: " << endl;
            ss >> wordInput;
            stringToFind = stripNonAlphaNum(wordInput);
            hashInstance.searchAndPrint(stringToFind, parsedQC);
        } else if (parsedQC == outF) {
            // cerr << "inside file case: " << endl;
            ss >> outFile;
            // Add changed outfile
        } else if ((parsedQC == qWord) or (parsedQC == qLetter)) {
            // cerr << "inside quit case: " << endl;
            cout << "Goodbye! Thank you and have a nice day." << endl;
            quitIt = true;
        } else {
            cerr << "inside sensitive case: " << endl;
            //check if possible to to have command not be one of the choices
            stringToFind = stripNonAlphaNum(parsedQC);
            cerr << "stringFinding: " << stringToFind << endl;
            hashInstance.searchAndPrint(stringToFind, parsedQC);
        }
    }
    return;
} 
