
#include "Dictionary.h"
#include "Boggle.h"

// Your code here
/*
 * Dictionary dict; // this dictionary object holds all valid words in the dictionary
    Dictionary wordsFound; // this dictionary object stores all the words found on the board
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE]; // update this board each time you visit a position on the board
 */
Boggle::Boggle() {
    // initialize dict with words from dictionary.txt
    dict.LoadDictionaryFile("dictionary.txt");

    // initialize each entry of board to empty string
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ""; // empty string, no space
        }
    }

    // initialize each entry of visited to false
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            visited[i][j] = 0; // 0 = false
        }
    }
}

// allow us to have a customize dictionary to load into the dictionary variable
Boggle::Boggle(string filename) {
    // initialize dict with words from dictionary.txt
    dict.LoadDictionaryFile(filename);

    // initialize each entry of board to empty string
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ""; // empty string, no space
        }
    }

    // initialize each entry of visited to false
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            visited[i][j] = 0; // 0 = false
        }
    }
}

// this function should copy each entry of board to this->board
// void Boggle::SetBoard(string (*board)[BOARD_SIZE][BOARD_SIZE]); ???
void Boggle::SetBoard(string (*board)[4]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            this->board[i][j] = board[i][j]; // ??????
        }
    }
}

// call solveBoardHelper 16 times for each position on the board
// this function is a wrapper function for SolveBoardHelper
// finds all the words on the current board stored by board and saves these words into wordsFound ????????
// this function should reset the wordsFound dictionary each time it is run ?????????
void Boggle::SolveBoard(bool printBoard, ostream &output) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            SolveBoardHelper(i, j, BOARD_SIZE, BOARD_SIZE, "", output);
            // SolveBoardHelper saves the words into wordsFound
        }
    }
    if (printBoard == true)
        PrintBoard(output);
}

// saves all the words from the last solve
// for each position on the board, find all the words on the board starting at this position
// this should use SaveDictionaryFile for the words found
void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile();
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0 ; j < BOARD_SIZE; j++) {
            //SolveBoardHelper(i, j, BOARD_SIZE, BOARD_SIZE, matrix[i][j], );
        }
    }
}

// the job of this function is to recursively check surrounding 8 positions
// check inbounds first then check if the position has been visited or not
// have some sort of string to remember what path, keep concatenating letters to the string
// use the isPrefix method to prevent exploration of paths that do not produce words
// need a way to remember all the previously visited spaces, a way to remember words you have already found
// order of base cases matters
void Boggle::SolveBoardHelper(int row, int col, int rowSz, int colSz, string currString, ostream& output) {

    // base case (?): check if the currString is a word or not
    if (dict.IsWord(currString)) {
        output << currString;
        wordsFound.AddWord(currString);
        //return; // ????? ex) CAT, CATS
    }

    // base case: inbound checking
    if (row < 0 || row > rowSz || col < 0 || col > rowSz) {
        return;
    }

    // base case: check if position has been visited or not through the visited matrix
    if (visited[row][col] != 0) {
        return;
    }

    // base case: check if the current string is a prefix or not
    if (!dict.IsPrefix(currString)) {
        return;
    }

    // mark each position as visited as you go through the matrix
    int mark = 1;
    visited[row][col] = mark;
    mark++;

    SolveBoardHelper(row - 1, col, BOARD_SIZE, BOARD_SIZE, currString + board[row-1][col], output); // N
    SolveBoardHelper(row - 1, col + 1, BOARD_SIZE, BOARD_SIZE, currString + board[row-1][col+1], output); // NE
    SolveBoardHelper(row, col + 1, BOARD_SIZE, BOARD_SIZE, currString + board[row][col+1], output); // E
    SolveBoardHelper(row + 1, col + 1, BOARD_SIZE, BOARD_SIZE, currString + board[row+1][col+1], output); // SE
    SolveBoardHelper(row + 1, col, BOARD_SIZE, BOARD_SIZE, currString + board[row+1][col], output); // S
    SolveBoardHelper(row + 1, col - 1, BOARD_SIZE, BOARD_SIZE, currString + board[row+1][col-1], output); // SW
    SolveBoardHelper(row, col - 1, BOARD_SIZE, BOARD_SIZE, currString + board[row][col-1], output); // W
    SolveBoardHelper(row - 1, col - 1, BOARD_SIZE, BOARD_SIZE, currString + board[row-1][col-1], output); // NW

    if (!dict.IsWord(currString)) { // ???????
        visited[row][col] = 0;
    }
}

void Boggle::PrintBoard(ostream &output) {
    for (int i = 0; i < BOARD_SIZE; i++) {

        // print the nth row in the board matrix
        for (int j = 0; j < BOARD_SIZE; j++) {
            // check if need to print out quotes or not
            if (visited[i][j] == 0) {
                output << "  " << board[i][j] << "  ";
            } else {
                output << " '" << board[i][j] << "' ";
            }
        }

        output << "\t";

        // print the nth row in the visited matrix
        for (int k = 0; k < BOARD_SIZE; k++) {
            output << "  " << visited[i][k] << " ";
        }
    };
}



// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}
