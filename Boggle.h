//
// Created by we7289 on 2/20/2021.
//

#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    Boggle();
    explicit Boggle(string filename);

    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

    void SolveBoard(bool printBoard, ostream& output);

    void SaveSolve(string filename);   // Saves all the words from the last solve.

    Dictionary GetDictionary();
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE]{};

    void PrintBoard(ostream& output);  //
    //SolveBoardHelper(/* Put any parameters you want here */);
    void SolveBoardHelper(int row, int col, const string& prefix, int step, bool printBoard, ostream& output);
};

#endif //BOGGLE_BOGGLE_H
