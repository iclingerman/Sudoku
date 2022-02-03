/*
 * Ian Clingerman 
 * Sudoku Solver 
 * 
 * Implementation file for Board class
 * 
 */ 

#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Board.h"

using namespace std;

/**
 * @brief Construct a new Board:: Board object with no values on the board
 * 
 */
Board::Board() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            this->board[i][j] = "123456789";
            this->boardGUI[i][j] = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
            this->boardGUI[i][j].setOutlineColor(sf::Color::Black);
            this->boardGUI[i][j].setOutlineThickness(3.0);
            this->boardGUI[i][j].setFillColor(sf::Color::White);
            this->boardGUI[i][j].setPosition(sf::Vector2f(i*50.f+50, j*50.f+90));
        }
    }
}

/**
 * @brief Construct a new Board:: Board object using values given in the input string
 * 
 * @param input The intial values of the board where '0' represents an empty space
 */
Board::Board(string input) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int a = input.at((i*9)+j) - '0';
            if (a == 0) {
                this->board[i][j] = "123456789";
            } else {
                this->board[i][j] = to_string(a);
            }
            this->boardGUI[i][j] = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
            this->boardGUI[i][j].setOutlineColor(sf::Color::Black);
            this->boardGUI[i][j].setOutlineThickness(3.0);
            this->boardGUI[i][j].setFillColor(sf::Color::White);
            this->boardGUI[i][j].setPosition(sf::Vector2f(i*50.f+50, j*50.f+90));
        }
    }
}


// void draw(sf::RenderTarget& target, sf::RenderStates states) {
//     for (int i = 0; i < 9; i++) {
//         for (int j = 0; j < 9; j++) {
//             target.draw(this->boardGUI[i][j]);
//         }
//     }
// }


/**
 * @brief Creates and returns a copy the board class
 * 
 * @return A copy of the board class 
 */
Board Board::copy() {
    Board rval(this->toString());
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            rval.board[i][j] = this->board[i][j];
        }
    }
    return rval;
}

/**
 * @brief returns a string representation of the sudoku board, where 0 represents a empty space
 * 
 * @return string representation of the sudoku board
 */
string Board::toString() {
    string msg = "";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->board[i][j].size() == 1) {
                msg += this->board[i][j];
            } else {
                msg += "0";
            }
        }
    }
    return msg;
}

/**
 * @brief Draws the sudoku board to the console
 * 
 */
void Board::drawBoard() {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << '\n' << "------+-------+------" << endl;
        } else {
            cout << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            if (this->board[i][j].size() > 1) {
                cout << '.' << ' ';
            } else {
                cout << this->board[i][j] << ' ';
            }
        }
    }
    cout << "\n\n";
}

/**
 * @brief Prints the possible values in the domains for each space on the sudoku board
 * 
 */
void Board::printDomains() {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << '\n' << "-----------------------------------------------------------------------" << endl;
        } else {
            cout << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << this->board[i][j] << "\t";
        }
    }
    cout << "\n\n";
}

/**
 * @brief Removes the given value from the domain of the space at i, j on the sudoku board
 * 
 * @param value The value to be removed from the domain
 * @param i The row of the space in the sudoku board
 * @param j The column of the space int eh sudoku board
 */
void Board::removeValueFromDomain(int value, int i, int j) {
    string newDomain = "";
    for (int k = 0; k < this->board[i][j].size(); k++) {
        if (this->board[i][j].at(k) - '0' != value) {
            newDomain += this->board[i][j].at(k);
        }
    }
    this->board[i][j] = newDomain;
}

/**
 * @brief Returns a boolean value of whether a value is in the domain of the space at i, j on the sudoku board
 * 
 * @param value The value to be checked
 * @param i The row of the space in the sudoku board
 * @param j The column of the space in the sudoku board
 * @return true if the value is located in the domain of the space
 * @return false if the value is not located in the domain of the space
 */
bool Board::domainContains(int value, int i, int j) {
    for (int k = 0; k < this->board[i][j].size(); k++) {
        if (this->board[i][j].at(k) - '0' == value) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Returns a list of integers that correspond to the box unit of the space at i, j on the sudoku board
 * 
 * @param i The row of the space in the sudoku board
 * @param j The column of the space in the sudoku board
 * @return list<int> a list of integers that correspond to the spaces in the box unit of the space at i, j. 
 * The numbers in the list are incoded as row*9+column corresponding to the row and column values of the spaces in the unit
 */
list<int> Board::generateBoxUnit(int i, int j) {
    list<int> box = list<int>();
    for (int k = i; k < i + 3; k++) {
        for (int l = j; l < j + 3; l++) {
            box.push_back((k%3+(i/3)*3)*9 + (l%3+(j/3)*3));
        }
    }
    return box;
}

/**
 * @brief Returns a list of integers that correspond to the row unit of the space at i, j on the sudoku board
 * 
 * @param i The row of the space in the sudoku board
 * @param j The column of the space in the sudoku board
 * @return list<int> a list of integers that correspond to the spaces in the row unit of the space at i, j. 
 * The numbers in the list are incoded as row*9+column corresponding to the row and column values of the spaces in the unit 
 */
list<int> Board::generateRowUnit(int i, int j) {
    list<int> column = list<int>();
    for (int k = i; k < i + 9; k++) {
        column.push_back(((k%9)*9) + j);
    }
    return column;
}

/**
 * @brief Returns a list of integers that correspond to the column unit of the space at i, j on the sudoku board
 * 
 * @param i The row of the space in the sudoku board
 * @param j The column of the space in the sudoku board
 * @return list<int> a list of integers that correspond to the spaces in the columnn unit of the space at i, j. 
 * The numbers in the list are incoded as row*9+column corresponding to the row and column values of the spaces in the unit
 */
list<int> Board::generateColUnit(int i, int j) {
    list<int> row = list<int>();
    for (int k = j; k < j +9; k++) {
        row.push_back(i*9 + (k%9));
    }
    return row;
}

/**
 * @brief Returns a list of integers that correspond to the peers of the given space on the board
 * 
 * @param i The row of the space in the sudoku board
 * @param j The column of the space in the sudoku board
 * @return list<int> a list of integer values that correspond to the peers of the space at i, j on the sudoku board. 
 * The numbers in the list are incoded as row*9+column corresponding to the row and column values of the spaces in the unit
 */
list<int> Board::generatePeers(int i, int j) {
    list<int> peers = generateBoxUnit(i, j);
    peers.merge(generateRowUnit(i, j));
    peers.merge(generateColUnit(i, j));
    peers.unique();
    peers.remove(i*9+j);
    return peers;
}

/**
 * @brief Runs through each of the spaces on the sudoku board and runs the elimniate method
 * 
 * @return false if the board is not consistent (unsolvable in it's current state)
 * @return true if the board is consistent 
 */
bool Board::solve() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(!eliminate(i, j)) {
                // cout << "No Solution (solve method)\n";
                return false;
            }
        }
    }
    // this->printDomains();
    return true;
}

/**
 * @brief Eliminates values from the domains of the given space's peers and potentially assigns a value to the space when 
 * it contains a unique value in one of it's units. 
 * 
 * 
 * @param i The row of the given space
 * @param j The column the given space 
 * @return false if the board is not consistent (unsolvable in it's current state)
 * @return true if the board is consistent 
 * 
 * If the value of the given space is assigned, then it loops through the peers of the given space and removes the value of the given space from 
 * each of its peer's domains. If one of the peers is also assigned with the value of the given space, then the board is inconsistent. 
 * Otherwise it checks whether the given space contains a value that is unique among one of the units it belongs to. If it contains a unique value, then
 * the space is assigned that value. 
 */
bool Board::eliminate(int i, int j) {
    if (this->board[i][j].size() == 1) { // if the value is already assigned
        list<int> peers = generatePeers(i, j);
        for (int x : peers) {
            if(this->board[x/9][x%9].size() == 1 && !(this->board[x/9][x%9].compare(this->board[i][j]))) {
                // cout << "No Solution (eliminate method)\n";
                return false;
            } else {
                this->removeValueFromDomain(this->board[i][j].at(0) - '0', x/9, x%9);
                continue;
            }
        }
    } else {  //Checks to see if the space contains a unique value in one of it's 3 units. If it does, it assigns the value to the space
        for (int k = 0; k < this->board[i][j].size(); k++) { //for each value in the domain
            int x = this->board[i][j].at(k) - '0';
            bool unique = true;
            //Box Unit
            for (int s : generateBoxUnit(i, j)){
                if (s == (i*9+j)) continue;
                if (domainContains(x, s/9, s%9)) {
                    unique = false;
                    break;
                }
            }
            if (unique) {
                this->board[i][j] = to_string(x);
                break;
            }
            //Row Unit
            for (int s : generateRowUnit(i, j)){
                if (s == (i*9+j)) continue;
                if (domainContains(x, s/9, s%9)) {
                    unique = false;
                    break;
                }
            }
            if (unique) {
                this->board[i][j] = to_string(x);
                break;
            }
            //Column Unit
            for (int s : generateColUnit(i, j)){
                if (s == (i*9+j)) continue;
                if (domainContains(x, s/9, s%9)) {
                    unique = false;
                    break;
                }
            }
            if (unique) {
                this->board[i][j] = to_string(x);
                break;
            }
        }
    }
    return true;
}

/**
 * @brief Searches through the tree of possible boards using a depth first method. It chooses it's branches by selecting the square 
 * with the smallest domain that is not yet assigned. 
 * 
 * @return true if the board is consistent
 * @return false if the board is inconsistent
 */
bool Board::search() {
    if(this->isSolved()) {
        cout << "SOLVED\n";
        // this->drawBoard();
        // cout << this->toString() << "\n";
        return true;
    }
    int curr = findSmallestDomain();
    for (int i = 0; i < this->board[curr/9][curr%9].size(); i++) {
        char assignment = this->board[curr/9][curr%9].at(i);
        Board b = this->copy();
        b.board[curr/9][curr%9] = assignment;
        if(b.solve()) {
            if(b.search()) {
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        this->board[i][j] = b.board[i][j];
                    }
                }
                return true;
            }
        } 
    }
    return false;
}

/**
 * @brief Finds the sudoku board square with the smallest domain that is not yet assigned
 * 
 * @return the integer representation of the sqaure on the board
 */
int Board::findSmallestDomain() {
    int smallestDomain = -1;
    int min = 10;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->board[i][j].size() != 1 && this->board[i][j].size() < min) {
                smallestDomain = i*9+j;
                min = this->board[i][j].size();
                if(min <= 2) {
                    return smallestDomain;
                }
            }
        }
    }
    if(min == 1) {
        return -1;
    }
    return smallestDomain;
}

/**
 * @brief Checks if the board is solved. 
 * Only checks if each domain is assigned, not if the board is valid
 * TODO: Change this to allAssigned() and implement a real isSolved method 
 * 
 * @return true if all of the squares have an assignment
 * @return false if there exists a square with multiple values in its domain
 */
bool Board::isSolved() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (this->board[i][j].size() != 1) {
                return false;
            }
        }
    }
    return true;
}