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
    /* Function: Creates an Dictionary object and takes in no arguments in the parameters
    * Precondition: None
    * Postcondition: A Dictionary object will be created
    */
    Dictionary();
    /* Function: Destroys the Dictionary object
    * Precondition: None
    * Postcondition: The Dictionary object will be destroyed
    */
    ~Dictionary();  // I will not require this
    /* Function: Copies all the contents of the dictionary in the parameters to this instance of the dictionary
    * Precondition: None
    * Postcondition: The dictionary object will be copied to this instance of the class
    */
    Dictionary(const Dictionary& otherDict);    // copy constructor
    /* Function: Constructor that takes in a filename in the parameters
    * Precondition: File must exist
    * Postcondition: A dictionary object will be created with the words that are in the filename
    */
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.

    /* Function: Overloaded = that copies all the contents of otherDict to this instance of dictionary
    * Precondition: None
     * Postcondition: All the contents of otherDict will be copied to this instance of dictionary
    */
    Dictionary& operator=(const Dictionary& otherDict);
    /* Function: Load all the words in filename to dictionary object
    * Precondition: File must exist
    * Postcondition: All words that are in the filename will be added to the dictionary object
    */
    void LoadDictionaryFile(string filename);
    /* Function: Write all the words into file name
    * Precondition: File must be opened
    * Postcondition: All words will be written to the filename
    */
    void SaveDictionaryFile(string filename);
    /* Function: Adds a word to the dictionary object
    * Precondition: Letters must be between a - z
    * Postcondition: Word will be added to the dictionary object
    */
    void AddWord(string word);
    /* Function: Destroys all the nodes in the tree
    * Precondition: Letters must be between a - z
    * Postcondition: Nodes will be destroyed, root is remade and number of words set back to 0
    */
    void MakeEmpty();

    /* Function: Checks if the word exists in the tree
    * Precondition: Letters must be between a - z
    * Postcondition: Returns a true or false value depending on whether or not the word exists in the tree
    */
    bool IsWord(string word);
    /* Function: Checks if prefix exists in the tree
    * Precondition: Letters must be between a - z
    * Postcondition: Returns a true or false value depending on whether or not the prefix exists
    */
    bool IsPrefix(string word);
    /* Function: Displays the current number of words in the tree
    * Precondition: None
    * Postcondition: Returns the number of words that exists in the tree
    */
    int WordCount();

private:

    class Node {
    public:
        // Your node structure here.
        // You can also use a struct if you like.

        // It is strongly recommended you create a constructor
        // to set default values
        Node* nodeArr[NUM_CHARS]; // array of node pointers. each index of the array will represent a letter.
        bool isWord = false; // indicates if the path to the node is a word

        /* Function: Default constructor that creates a node object
        * Precondition: None
        * Postcondition: A node will be created with all indexes pointing to nullptr
        */
        Node();
    };



    Node* root;
    int numWords;

    // This function is used by the
    // copy constructor and the assignment operator.
    /* Function: Wrapper function for copyHelper
    * Precondition: None
    * Postcondition: This instance of dictionary object will be made empty then all the contents from otherDict will be copied over
    */
    void copyOther(const Dictionary& otherDict);

    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.
    /* Function: Helper function that destroys all the nodes in the object
    * Precondition: None
    * Postcondition: All the nodes in the object will be destroyed
    */
    void destroyHelper(Node*& thisTree); // change to pass by reference?????
    /* Function: Helper function that copies all the contents of otherDict to this instance of the dictionary class
    * Precondition: None
    * Postcondition: All the contents of otherDict will be copied to this instance of dictionary class
    */
    void copyHelper(Node*& thisTree, Node* otherTree);
    /* Function: Helper function that writes out all the words that exists into a file
   * Precondition: None
   * Postcondition: All the words that exists will be written to a file
   */
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
};

#endif //BOGGLE_DICTIONARY_H
