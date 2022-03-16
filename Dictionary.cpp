

#include "Dictionary.h"

//default constructor
Dictionary::Dictionary() {
    root = nullptr;
    numWords = 0;
}

Dictionary::Dictionary(string filename){
    //Pre: the name of an input file gets passed in to the the constructor
    //Post: a dictionary object gets created with words from the file that is passed in

    root = nullptr;
    numWords = 0;

    LoadDictionaryFile(filename);
}



// This function is complete.
Dictionary::Dictionary(const Dictionary &otherDict) {
    *this = otherDict;  // This function is complete.
}

Dictionary& Dictionary::operator=(const Dictionary &otherDict) {
    MakeEmpty();
    numWords = otherDict.numWords;

    if (otherDict.root == nullptr)
        return *this;
    this->root->isWord = otherDict.root->isWord;

    this->root = new Node;
    for(int i = 0; i < NUM_CHARS; i++){
        root->letterBranch[i] = nullptr;
    }
    root->isWord = false;

    // Copy each branch
    for (int i = 0; i < NUM_CHARS; i++) {
        copyHelper(root->letterBranch[i], otherDict.root->letterBranch[i]);
    }

    return *this;
}

void Dictionary::copyHelper(Node*& thisTree, Node*& otherTree) {
    if (otherTree == nullptr) {
        thisTree = nullptr;
        return;
    }

    thisTree=new Node;
    for (int i = 0; i < NUM_CHARS; i++) {
        copyHelper(thisTree->letterBranch[i], otherTree->letterBranch[i]);
    }
    thisTree->isWord=otherTree->isWord;

}

void Dictionary::LoadDictionaryFile(string filename) {
    ifstream inFile;
    inFile.open(filename);
    if (inFile.fail()) {
        throw DictionaryError(filename+" failed to open");
    }
    string word;
    while(inFile >> word){ //while there are words to read from the file
        AddWord(word); //words get added
    }
    inFile.close();
}

void Dictionary::SaveDictionaryFile(string filename) {
    ofstream outFile;
    outFile.open(filename); //opens the file that is passed in
    if (outFile.fail()) {
        throw DictionaryError(filename+" failed to open");
    }

    SaveDictionaryHelper(root, "", outFile);
//    string letter = " ";
//    for (int i = 0; i < NUM_CHARS; i++) {
//        letter[0] = (char)(i + (int) 'a');
//        cout << letter << endl;
//
//    }

    outFile.close();
}

void Dictionary::SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile) {
    if (curr == nullptr)
        return;

    if (curr->isWord) {
        cout << currPrefix << endl;
        outFile << currPrefix << endl;
    }

    string letter = " ";
    for (int i = 0; i < NUM_CHARS; i++) {
        letter[0] = (char)(i + (int) 'a');
        SaveDictionaryHelper(curr->letterBranch[i], currPrefix+letter, outFile);
    }
}

void Dictionary::AddWord(string word){
    //Pre: word passed in to be added to the dictionary
    //Post: will add a path for the inserted word and set isWord to true at the leaf node

    if(root == nullptr){
        root = new Node;
        for(int i = 0; i < NUM_CHARS; i++){
            root->letterBranch[i] = nullptr;
        }
    }

    Node* curr;
    curr = root;
    for(int c = 0; c < word.length();c++){ //for (each character c of the word)
        int index = (int) word[c] - (int) 'a'; //gets the integer value for the ascii code at the particular index of the string that is being assessed
        if(numWords == 0 || curr->letterBranch[index] == nullptr){ //if (the branch for character c is NULL)
            curr->letterBranch[index] = new Node; //set the branch of character c = new Node.
            for(int ind = 0; ind < NUM_CHARS; ind++){
                (curr->letterBranch[index])->letterBranch[ind] = nullptr;
            }
            curr->letterBranch[index]->isWord = false; //set flag of this new Node to false
        }
        curr = curr->letterBranch[index]; //currNode = the pointer index of character c
    }
    curr->isWord = true; // Set the flag at the currNode to true
    numWords++; //increments the number of the words in the dictionary
}

void Dictionary::destroyHelper(Node *thisTree) {
    if (thisTree == nullptr) {
        return;
    }

    for (int i = 0; i < NUM_CHARS; i++)
    {
        destroyHelper(thisTree->letterBranch[i]);
    }

    delete thisTree;
}

void Dictionary::MakeEmpty() {
    destroyHelper(root);
    root = new Node;
    for(int i = 0; i < NUM_CHARS; i++){
        root->letterBranch[i] = nullptr;
    }
    root->isWord = false;
    numWords = 0;
}

bool Dictionary::IsWord(string word){
    //Pre: word passed in to see if check whether it is a real word or not
    //Post: returns true if the path is found and true, returns false if path is not found in the tree

    if(root == nullptr){
        return false;
    }

    Node* curr;
    curr = root;

    for(int c = 0; c < word.length(); c++){ //for every character in the word
        int index = (int) word[c] - (int) 'a';
        if(curr->letterBranch[index] == nullptr){ //if a path for the current letter does not exist, it will return false
            return false;
        }
        curr = curr->letterBranch[index]; //will go to the next node
    }

    return curr->isWord;
}

bool Dictionary::IsPrefix(string word) {
    //Pre: word passed in to see if there is an existing path to continue to find out if the word is a real word
    //Post: returns true if there is a viable path for the word, returns false if there is no path

    if(root == nullptr){
        return false;
    }

    Node* curr;
    curr = root;

    for(int c = 0; c < word.length(); c++){ // for each character of the word
        int index = (int) word[c] - (int) 'a';
        if(curr->letterBranch[index] == nullptr){ //if the current character does not have a path will return false
            return false;
        }
        curr = curr->letterBranch[index]; // will set current node to the next one in the path
    }
    return true; //if the for loop executes without returning false then it is a valid prefix and will return true

}


int Dictionary::WordCount() {
    //Post: returns the amount of words in the
    return numWords;
}











