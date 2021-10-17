#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    /* Function: Creates a Boggle object and takes in no arguments in the parameters
    * Precondition: None
    * Postcondition: A Boggle object will be created with the default dictionary "dictionary.txt"
    */
    Boggle();  // load "dictionary.txt" into dict
    /* Function: Creates a Boggle object and takes filename in the parameters
    * Precondition: File name must exists
    * Postcondition: A Boggle object will be created with using a customized dictionary loaded into the dictionary variable
    */
    explicit Boggle(string filename);  // load filename into dict
    /* Function: Copies all the contents from "board" into this instance of the board
    * Precondition: None
    * Postcondition: All the contents of "board" will be copied to this instance of the class
    */
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);
    /* Function: A wrapper function for SolveBoardHelper. Finds all the words in the board and saves it into the wordsFound dictionary
    * Precondition: None
    * Postcondition: All the words found will be loaded into the wordsFound dictionary.
     * The words may or may not be printed depending on the user's selection for printBoard.
     * The words will also be outputted to the ostream object.
    */
    void SolveBoard(bool printBoard, ostream& output);
    /* Function: Saves all the words from the last solve
    * Precondition: None
    * Postcondition: All the words found will be loaded into the filename
    */
    void SaveSolve(string filename);   // Saves all the words from the last solve.
    /* Function: Function that returns the dictionary object
    * Precondition: None
    * Postcondition: Dictionary object will be returned
    */
    Dictionary GetDictionary();
    /* Function: Function that returns the wordsFound object
    * Precondition: None
    * Postcondition: wordsFound object will be returned
    */
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    /* Function: Function that prints the board matrix and the visited matrix
    * Precondition: None
    * Postcondition: The board matrix and visited matrix will be returned
    */
    void PrintBoard(ostream& output);
    /* Function: Helper function for SolveBoard that finds all the words that exists on the board
    * Precondition: None
    * Postcondition: The words that exists on the board will be found and saved into wordsFound
    */
    void SolveBoardHelper(/* Put any parameters you want/need here */int row, int col, int startRow, int startCol, string currString, ostream& output, int mark, bool printBoard);
};

#endif //BOGGLE_BOGGLE_H
