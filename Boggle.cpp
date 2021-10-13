
#include "Dictionary.h"
#include "Boggle.h"

// Your code here
/*
 * Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];
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

void Boggle::SetBoard(string (*board)[4]) {

}

void Boggle::SolveBoard(bool printBoard, ostream &output) {

}

void Boggle::SaveSolve(string filename) {

}

void Boggle::PrintBoard(ostream &output) {

}

void Boggle::SolveBoardHelper() {

}

// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}
