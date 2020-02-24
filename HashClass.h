 * HashClass.h
 * COMP15
 * Spring 2019
 *
 *
 * Author: Tim White 
 * Date: 11/15/2019

#ifndef HASHCLASS_H_
#define HASHCLASS_H_

#include <vector>
#include <string>


struct lineContent {
    string line;
    int lineNum;
};

struct Indexes {
    int line;
    int path;
};

struct wordContent{
    string word;
    vector<Indexes>LPInfo;
};

struct bucketData{
    string lowCaseWord;
    vector<wordContent>WCVec;
};

class HashClass 
{
public:
    HashClass();
    // filesOpened is for testing purposes only
    void mainHashing(string path, int filesOpened);
    void searchAndPrint(string wordToSearch, string command, ostream &out);


private:
    int wordsStored;
    int capacity;
    vector<bucketData> *data;
    vector<string>paths;
    vector<lineContent>lineStuff;
    void printForTest();
    void expand();
    void searchPrintSensitive(int bucket, string wordToSearch, string lowWord, 
                              ostream &out);
    void searchPrintInsensitive(int bucket, string wordToSearch, ostream &out);
    void hashAndPush(wordContent WC, Indexes currIndexes);
};

#endif
