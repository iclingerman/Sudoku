/*
 * Ian Clingerman 
 * Sudoku Solver 
 * 
 * Header file for Board class
 * 
 */ 

#include <string>
#include <list>

using namespace std;

class Board {
    private:
        string board[9][9];

    public:
        Board();
        Board(string);
        Board copy();
        string toString();
        void drawBoard();
        void printDomains();
        void removeValueFromDomain(int value, int i, int j);
        bool domainContains(int value, int i, int j);
        list<int> generateBoxUnit(int i, int j);
        list<int> generateRowUnit(int i, int j);
        list<int> generateColUnit(int i, int j);
        list<int> generatePeers(int i, int j);

        bool solve();
        bool eliminate(int i, int j);
        bool search();
        int findSmallestDomain();
        bool isSolved();
};