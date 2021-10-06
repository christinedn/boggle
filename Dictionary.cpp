#include "Dictionary.h"

// Your code here

// default constructor
Dictionary::Dictionary() {
    root = new Node;

    // make each position of the branch array null
    for (int i = 0; i < NUM_CHARS; i++) {
        root->charArr[i] = nullptr;
    }

    root->isWord = false;
    numWords = 0;
}

// destructor
//Dictionary::~Dictionary() {
//
//}

// copy constructor
// copies all the contents of otherDict to this
// use copyOther function complete this function
Dictionary::Dictionary(const Dictionary &otherDict) {
    root = new Node;
    numWords = 0;
    copyOther(otherDict);
}

Dictionary::Dictionary(string filename) {

}

//Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
//    return <#initializer#>;
//}

void Dictionary::LoadDictionaryFile(string filename) {

}

void Dictionary::SaveDictionaryFile(string filename) {

}

void Dictionary::AddWord(string word) {

}

void Dictionary::MakeEmpty() {

}

bool Dictionary::IsWord(string word) {
    return false;
}

bool Dictionary::IsPrefix(string word) {
    return false;
}

int Dictionary::WordCount() {
    return 0;
}

// helper function for the copy constructor
void Dictionary::copyOther(const Dictionary &otherDict) {
    MakeEmpty();
    copyHelper(root, otherDict.root);
    numWords = otherDict.numWords;
}

// helper function for the copyOther function
void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    // this checks if you are copying an empty tree?
    if (otherTree == nullptr) {
        thisTree = nullptr;
        return;
    }


    thisTree = new Node;
    thisTree->isWord = otherTree->isWord;
    for (int i = 0; i < NUM_CHARS; i++) {
        copyHelper(thisTree->charArr[i], otherTree->charArr[i]);
    }
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {

}



void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {

}
