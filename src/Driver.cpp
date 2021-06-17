/*
 * Ian Clingerman 
 * Sudoku Solver 
 * 
 * Driver for Sudoku Solver Program
 * 
 */ 

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <list>
#include "Board.h"

using namespace std;


int main() {
    srand((unsigned) time(0));
    int r = rand() % 54 + 1;
    cout << r << '\n';
    string line;
    ifstream boards;
    boards.open("./data/formattedPuzzles.txt");
    for (int i = 0; i <= r; i++) {
        getline(boards, line);
    }
    Board b(line);
    b.drawBoard();
    b.search();
    b.drawBoard();
    cout << b.toString() << "\n";
}