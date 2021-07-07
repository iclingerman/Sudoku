/*
 * Ian Clingerman 
 * Sudoku Solver 
 * 
 * Driver for Sudoku Solver Program with Graphics
 * 
 */ 

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <list>
#include "Board.h"


void updateBoard(std::string board, sf::Text numbers[9][9]) {
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::string str = "";
            if(board.at(i*9+j) != '0') {
                str += board.at(i*9+j);
            } else {
                str += " ";
            }
            numbers[i][j].setString(str);
        }
    }
}

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


    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Sudoku Solver", sf::Style::Default, settings);

    sf::Font font;
    if(!font.loadFromFile("./data/SEGOEUI.TTF")) {
        std::cout << "Error loading font\n";
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Sudoku Solver");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(10, 0));


    sf::RectangleShape board[9][9];
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            board[i][j] = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
            board[i][j].setOutlineColor(sf::Color::Black);
            
            board[i][j].setOutlineThickness(3.0);
            board[i][j].setFillColor(sf::Color::White);
            board[i][j].setPosition(sf::Vector2f(i*50.f+50, j*50.f+90));
        }
    }

    sf::RectangleShape line1(sf::Vector2f(450.f, 4.f));
    line1.setFillColor(sf::Color::Black);
    line1.setPosition(sf::Vector2f(50.f, 240.f));

    sf::RectangleShape line2(sf::Vector2f(450.f, 4.f));
    line2.setFillColor(sf::Color::Black);
    line2.setPosition(sf::Vector2f(50.f, 390.f));

    sf::RectangleShape line3(sf::Vector2f(4.f, 450.f));
    line3.setFillColor(sf::Color::Black);
    line3.setPosition(sf::Vector2f(200.f, 90.f));

    sf::RectangleShape line4(sf::Vector2f(4.f, 450.f));
    line4.setFillColor(sf::Color::Black);
    line4.setPosition(sf::Vector2f(350.f, 90.f));

    sf::Text numbers[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            numbers[i][j].setFont(font);
            numbers[i][j].setCharacterSize(48);
            
            numbers[i][j].setFillColor(sf::Color::Black);
            numbers[i][j].setPosition(sf::Vector2f(i*50.f+60, j*50.f+85));
        }
    }

    updateBoard(b.toString(), numbers);

    //run the program as long as the window is open
    while(window.isOpen()) {
        //Check all of the window's events that were triggered
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed: //"close requested" event: we close the window
                    window.close();
                    break;
                
                case sf::Event::TextEntered:
                    if(event.text.unicode < 128) {
                        std::cout << "Character Typed: " << static_cast<char>(event.text.unicode) << '\n';
                    }
                    break;
                
                case sf::Event::MouseButtonPressed:
                    std::cout << "x = " << event.mouseButton.x << ", y = " << event.mouseButton.y << '\n';
                    std::cout << "NOW SOLVING\n";
                    b.search();
                    updateBoard(b.toString(), numbers);
                default:
                    break;
            }
        }
        //draw loop
        window.clear(sf::Color(0, 102, 255, 255));
        
       
        window.draw(text);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                window.draw(board[i][j]);
                window.draw(numbers[i][j]);
            }
        }

        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);

        window.display();
    }

    return 0;
}

