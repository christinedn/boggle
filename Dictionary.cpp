#include "Dictionary.h"
#include <fstream>

// Your code here
// default constructor for Node
Dictionary::Node::Node() {
    for (int i = 0; i < NUM_CHARS; i++) {
        nodeArr[i] = nullptr;
    }
}


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

    for (int i = 0; i < NUM_CHARS; i++) {
        root->nodeArr[i] = nullptr;
    }

    root->isWord = false;
    numWords = 0;

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
    while (!myFile.eof()) {
        myFile >> inputWord;
        AddWord(inputWord);
    }
    myFile.close();
}

void Dictionary::SaveDictionaryFile(string filename) {
    ofstream myFile;
    myFile.open(filename);

    if (!myFile.is_open())
        throw DictionaryError(filename + " failed to open");

    // write all words that exists in the tree to the file
    // loop through all indexes in root to see which branches exist
    for (int i = 0; i < NUM_CHARS; i++) {
        if (root->nodeArr[i] != nullptr) {
            // at this point, that means the there is a branch from that letter
            // convert that index into a string
            char convertToChar = char(i + (int)'a');
            string s1{convertToChar};
            // pass in that string to SaveDictionaryHelper
            SaveDictionaryHelper(root->nodeArr[i], s1, myFile);
        }
    }
    myFile.close();
}

void Dictionary::AddWord(string word) {
    Node* curr = root;
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
            // make a branch from letterIndex to a new node
            curr->nodeArr[letterIndex] = new Node;
            // set flag of this new node to false
            curr->nodeArr[letterIndex]->isWord = false;
        }
        curr = curr->nodeArr[letterIndex];
    }
    // at this point, curr is at the node in which a path exists for a word
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
            curr = curr->nodeArr[letterIndex]; // ??????
        } else {
            return false;
        }

        if (i == word.length()-1) {
            if (curr->isWord == true) {
                return true;
            }
        }
    }
    return false;
}

bool Dictionary::IsPrefix(string word) {
    Node* curr = root;

    // an empty string is a prefix of any string
    if (word.length() == 0) {
        return true;
    }

    for (int i = 0; i < word.length(); i++) {
        // check if letters are between 'a' and 'z'
        // a = 97, z = 122 in ASCII
        if ((int)word[i] < 97 || (int)word[i] > 122) {
            throw DictionaryError("Invalid character");
        }

        int letterIndex = (int)word[i] - (int)'a';
        if (curr->nodeArr[letterIndex] != nullptr) {
            curr = curr->nodeArr[letterIndex]; // ??????
        } else {
            return false;
        }

        if (i == word.length()-1) {
            return true;
        }
    }
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
    if (curr == nullptr)
        return;

    if (curr->isWord == true) {
        outFile << currPrefix << endl;
    }

    for (int i = 0; i < NUM_CHARS; i++) {
        if (curr->nodeArr[i] != nullptr) {
            // convert from int to string
            char convertToChar = char(i + (int)'a');
            string s1{convertToChar};
            SaveDictionaryHelper(curr->nodeArr[i], currPrefix + s1, outFile);
        }
    }
}