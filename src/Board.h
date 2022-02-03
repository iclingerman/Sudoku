/*
 * Ian Clingerman 
 * Sudoku Solver 
 * 
 * Header file for Board class
 * 
 */ 

#include <string>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class Board : public sf::Drawable {
    private:
        string board[9][9];
        sf::RectangleShape boardGUI[9][9];
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    target.draw(this->boardGUI[i][j]);
                }
            }
        }

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