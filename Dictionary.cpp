#include "Dictionary.h"
#include <fstream>

// Your code here

// default constructor
Dictionary::Dictionary() {
    root = new Node;

    // make each position of the branch array null
    for (int i = 0; i < NUM_CHARS; i++) {
        root->nodeArr[i] = nullptr;
    }

    root->isWord = false;
    numWords = 0;
}

Dictionary::~Dictionary() {
    destroyHelper(root); // ???????
}

Dictionary::Dictionary(const Dictionary &otherDict) {
    root = new Node;
    numWords = 0;
    copyOther(otherDict);
}

Dictionary::Dictionary(string filename) {
    root = new Node;
    LoadDictionaryFile(filename);
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    // i = i;
    if (this != &otherDict) {
        copyOther(otherDict);
    }
    return *this;
}

void Dictionary::LoadDictionaryFile(string filename) {
    ifstream myFile;
    string inputWord;
    myFile.open(filename);

    if (!myFile.is_open())
        throw "File failed to open";

    // read contents of the file
    while (myFile) {
        myFile >> inputWord;
        AddWord(inputWord);
    }
    myFile.close();
}

void Dictionary::SaveDictionaryFile(string filename) {
    ofstream myFile;
    myFile.open(filename);

    if (!myFile.is_open())
        throw DictionaryError(filename + "failed to open");

    // write all words that exists in the tree to the file
    SaveDictionaryHelper();

    myFile.close();
}

// this function is not complete
void Dictionary::AddWord(string word) {
    Node* curr = root;
    Node* newNode;
    for (int i = 0; i < word.length(); i++) {

        // check if letters are between 'a' and 'z'
        // a = 97, z = 122 in ASCII
        if ((int)word[i] < 97 || (int)word[i] > 122) {
            throw DictionaryError("Invalid character");
        }

        // create a variable to find which index the letter is located in the nodeArr
        int letterIndex = (int)word[i] - (int)'a';
        // check if the branch for that character is nullptr
        if (curr->nodeArr[letterIndex] == nullptr) {
            newNode = new Node();
            // make a branch from letterIndex to newNode
            curr->nodeArr[letterIndex]->next = newNode; // ???????
            newNode->isWord = false;
        }
        curr = newNode; // ????????????
    }
    curr->isWord = true;
    numWords++;
}

void Dictionary::MakeEmpty() {
    destroyHelper(root);

    // remake root
    root = new Node;
    numWords = 0;
}

bool Dictionary::IsWord(string word) {
    Node* curr = root;
    for (int i = 0; i < word.length(); i++) {

        // check if letters are between 'a' and 'z'
        // a = 97, z = 122 in ASCII
        if ((int)word[i] < 97 || (int)word[i] > 122) {
            throw DictionaryError("Invalid character");
        }

        int letterIndex = (int)word[i] - (int)'a';
        if (curr->nodeArr[letterIndex] != nullptr) {
            curr = curr->nodeArr[letterIndex]->next; // ??????
        } else {
            return false;
        }

        if (i == word.length()-1) {
            if (curr->isWord == true) {
                return true;
            }
        }
    }
    //return false;
}

bool Dictionary::IsPrefix(string word) {
    Node* curr = root;
    for (int i = 0; i < word.length(); i++) {

        // check if letters are between 'a' and 'z'
        // a = 97, z = 122 in ASCII
        if ((int)word[i] < 97 || (int)word[i] > 122) {
            throw DictionaryError("Invalid character");
        }

        int letterIndex = (int)word[i] - (int)'a';
        if (curr->nodeArr[letterIndex] != nullptr) {
            curr = curr->nodeArr[letterIndex]->next; // ??????
        } else {
            return false;
        }

        if (i == word.length()-1) {
            return true;
        }
    }
    //return false;
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
        copyHelper(thisTree->nodeArr[i], otherTree->nodeArr[i]);
    }
}

void Dictionary::destroyHelper(Dictionary::Node *&thisTree) {
    if (thisTree == nullptr) {
        return;
    }
    for (int i = 0; i < NUM_CHARS; i++) {
        destroyHelper(thisTree->nodeArr[i]);
        delete thisTree->nodeArr[i];
    }
}



void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {

}
