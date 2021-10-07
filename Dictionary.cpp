#include "Dictionary.h"

// Your code here

// default constructor
Dictionary::Dictionary() {
    root = new Node;

    // make each position of the branch array null
    for (int i = 0; i < NUM_CHARS; i++) {
        root->charArr[i] = nullptr;
        // set each index of char charArr boolean to false
        root->charArr[i]->isWord = false;
    }

    //root->isWord = false;
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

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    // i = i;
    if (this != &otherDict) {
        copyOther(otherDict);
    }
    return *this;
}

void Dictionary::LoadDictionaryFile(string filename) {

}

void Dictionary::SaveDictionaryFile(string filename) {

}

void Dictionary::AddWord(string word) {
    Node* curr = root;
    Node* newNode;
    for (int i = 0; i < word.length(); i++) {

        // check if letters are between 'a' and 'z'
        // a = 97, z = 122 in ASCII
        if ((int)word[i] < 97 || (int)word[i] > 122) {
            throw DictionaryError("Invalid character");
        }

        // create a variable to find which index the letter is located in the charArr
        int letterIndex = (int)word[i] - (int)'a';
        // check if the branch for that character is nullptr
        if (curr->charArr[letterIndex] == nullptr) {
            newNode = new Node();
            // make a branch from letterIndex to newNode->charArr[word[next letter]];
            curr->charArr[letterIndex]->next = newNode;
            newNode->isWord = false; // ????????
        }
        curr = newNode;
    }
    int lastLetterIndex = (int)word[word.length()-1] - (int)'a';
    curr->charArr[lastLetterIndex]->isWord = true;
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
    return numWords;
}

// helper function for the copy constructor
void Dictionary::copyOther(const Dictionary &otherDict) {
    MakeEmpty();
    copyHelper(root, otherDict.root);
    numWords = otherDict.numWords;
}

// helper function for the copyOther function
void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    // this checks if you are copying an empty tree
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
