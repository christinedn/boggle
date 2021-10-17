
#include "Dictionary.h"
#include "Boggle.h"

// Your code here

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

// allow us to have a customized dictionary to load into the dictionary variable
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
            visited[i][j] = 0;
        }
    }
}

void Boggle::SetBoard(string board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            this->board[i][j] = board[i][j];
        }
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            SolveBoardHelper(i, j, i, j, board[i][j], output, 1, printBoard);
        }
    }
}

void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}


void Boggle::SolveBoardHelper(int row, int col, int startRow, int startCol, string currString, ostream& output, int mark, bool printBoard) {
    // base case: inbound checking
    if (row < 0 || row > (BOARD_SIZE-1) || col < 0 || col > (BOARD_SIZE-1)) {
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
    visited[row][col] = mark;
    mark++;

    // base case (?): check if the currString is a word or not
    if (dict.IsWord(currString)) {
        output << currString << endl;
        wordsFound.AddWord(currString);
        if (printBoard) {
            PrintBoard(output);
        }
    }

    string north, northeast, east, southeast, south, southwest, west, northwest;
    // the if statements below will combine the N/NE/E/etc.. strings accordingly depending on whether or not they exist
    if (row == 0) {
        northwest = currString;
        north = currString;
        northeast = currString;
    } else {
        if (col == 0) {
            northwest = currString;
        } else {
            northwest = currString + board[row-1][col-1];
        }
        north = currString + board[row-1][col];
        if (col == BOARD_SIZE - 1) {
            northeast = currString;
        } else {
            northeast = currString + board[row-1][col+1];
        }
    }

    if (col == BOARD_SIZE-1) {
        east = currString;
        southeast = currString;
    } else {
        east = currString + board[row][col+1];
        if (row == BOARD_SIZE - 1) {
            southeast = currString;
        } else {
            southeast = currString + board[row+1][col+1];
        }
    }

    if (row == BOARD_SIZE-1) {
        south = currString;
        southwest = currString;
    } else {
        if (col == 0) {
            southwest = currString;
        } else {
            southwest = currString + board[row+1][col-1];
        }
        south = currString + board[row+1][col];
    }

    if (col == 0) {
        west = currString;
    } else {
        west = currString + board[row][col-1];
    }

    SolveBoardHelper(row - 1, col, startRow, startCol, north, output, mark, printBoard); // N
    SolveBoardHelper(row - 1, col + 1, startRow, startCol, northeast, output, mark, printBoard); // NE
    SolveBoardHelper(row, col + 1, startRow, startCol, east, output, mark, printBoard); // E
    SolveBoardHelper(row + 1, col + 1, startRow, startCol, southeast, output, mark, printBoard); // SE
    SolveBoardHelper(row + 1, col, startRow, startCol, south, output, mark, printBoard); // S
    SolveBoardHelper(row + 1, col - 1, startRow, startCol, southwest, output, mark, printBoard); // SW
    SolveBoardHelper(row, col - 1, startRow, startCol, west, output, mark, printBoard); // W
    SolveBoardHelper(row - 1, col - 1, startRow, startCol, northwest, output, mark, printBoard); // NW

    // setting the last visited position back to 0
    if (dict.IsPrefix(currString) && !(row == startRow && col == startCol)) {
        visited[row][col] = 0;
    } else {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (i == startRow && j == startCol) {
                        continue;
                    }
                    visited[i][j] = 0;
                }
            }
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
        cout << endl;
    }
}



// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}
