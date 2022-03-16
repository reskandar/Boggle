//
// Created by we7289 on 2/20/2021.
//

#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

class DictionaryError{
public:
    explicit DictionaryError(string msg) {
        this->msg = msg;
    }
    string Msg(){
        return msg;  // returns king of flavor
    }
private:
    string msg;
};

class Dictionary
{

public:
    Dictionary();
    // ~Dictionary();  // I will not require this
    Dictionary(const Dictionary& otherDict);    // copy constructor
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.

    Dictionary& operator=(const Dictionary& otherDict);
    void LoadDictionaryFile(string filename);
    void SaveDictionaryFile(string filename);

//    void SaveLatex(string filename);

    void AddWord(string word);
    void MakeEmpty();

    bool IsWord(string word);
    bool IsPrefix(string word);
    int WordCount();

private:

    class Node {
    public:
        Node() {
            for (int i = 0; i < 26; i++) {
                letterBranch[i] = nullptr;
            }
            isWord = false;
        }
        // Your node structure here
        Node* letterBranch[26];
        bool isWord;

    };

    Node* root;
    int numWords;

    void destroyHelper(Node* thisTree);
    void copyHelper(Node*& thisTree, Node*& otherTree);
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
    // Any private methods you need/want

//    void SaveHelper(string tab, string prefix, Node* curr, ostream& out);
};

#endif //BOGGLE_DICTIONARY_H
