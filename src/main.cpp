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
#include "Button.h"


void updateBoard(std::string board, sf::Text numbers[9][9]) {
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::string str = "";
            if(board.at(i+9*j) != '0') {
                str += board.at(i+9*j);
            } else {
                str += " ";
            }
            numbers[i][j].setString(str);
        }
    }
}

int main() {
    //52 is hard? 
    srand((unsigned) time(0));
    int r = rand() % 54 + 1;
    cout << r << '\n';
    string line;
    ifstream boards;
    boards.open("./data/formattedPuzzles.txt");
    // r = 55;
    for (int i = 0; i <= r; i++) {
        getline(boards, line);
    }
    Board b(line);
    // Board b();
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

    sf::Text solveButtonLabel;
    solveButtonLabel.setFont(font);
    solveButtonLabel.setCharacterSize(32);
    solveButtonLabel.setFillColor(sf::Color::Black);
    solveButtonLabel.setString("Solve");

    sf::Text resetButtonLabel;
    resetButtonLabel.setFont(font);
    resetButtonLabel.setCharacterSize(32);
    resetButtonLabel.setFillColor(sf::Color::Black);
    resetButtonLabel.setString("Reset");

    Button solveButton(solveButtonLabel, sf::Vector2f(560.f, 90.f), sf::Vector2f(175.f, 47.f), sf::Color::White);
    Button resetButton(resetButtonLabel, sf::Vector2f(560.f, 190.f), sf::Vector2f(175.f, 47.f), sf::Color::White);


    // sf::RectangleShape board[9][9];
    // for(int i = 0; i < 9; i++) {
    //     for (int j = 0; j < 9; j++) {
    //         board[i][j] = sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    //         board[i][j].setOutlineColor(sf::Color::Black);
            
    //         board[i][j].setOutlineThickness(3.0);
    //         board[i][j].setFillColor(sf::Color::White);
    //         board[i][j].setPosition(sf::Vector2f(i*50.f+50, j*50.f+90));
    //     }
    // }

    sf::RectangleShape verticalLines[8];
    sf::RectangleShape horizontalLines[8];
    for (int i = 1; i < 9; i++) {
        if(i % 3 != 0) {
            verticalLines[i-1] = sf::RectangleShape(sf::Vector2f(3.f, 450.f));
            horizontalLines[i-1] = sf::RectangleShape(sf::Vector2f(450.f, 3.f));
        } else {
            verticalLines[i-1] = sf::RectangleShape(sf::Vector2f(5.f, 450.f));
            horizontalLines[i-1] = sf::RectangleShape(sf::Vector2f(450.f, 5.f));
        }
        verticalLines[i-1].setFillColor(sf::Color::Black);
        verticalLines[i-1].setPosition(sf::Vector2f(i*50.f+50, 90.f));
        horizontalLines[i-1].setFillColor(sf::Color::Black);
        horizontalLines[i-1].setPosition(sf::Vector2f(50.f, i*50.f+90));
    }
    // sf::RectangleShape board = sf::RectangleShape(sf::Vector2f(450.f, 450.f));
    // board.setFillColor(sf::Color::White);
    // board.setPosition(sf::Vector2f(50.f, 90.f));
    // board.setOutlineThickness(5.f);
    // board.setOutlineColor(sf::Color::Black);


    sf::RectangleShape line1(sf::Vector2f(450.f, 5.f));
    line1.setFillColor(sf::Color::Black);
    line1.setPosition(sf::Vector2f(50.f, 240.f));

    sf::RectangleShape line2(sf::Vector2f(450.f, 5.f));
    line2.setFillColor(sf::Color::Black);
    line2.setPosition(sf::Vector2f(50.f, 390.f));

    sf::RectangleShape line3(sf::Vector2f(5.f, 450.f));
    line3.setFillColor(sf::Color::Black);
    line3.setPosition(sf::Vector2f(200.f, 90.f));

    sf::RectangleShape line4(sf::Vector2f(5.f, 450.f));
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
                    
                    if(solveButton.checkClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "NOW SOLVING\n";
                        b.search();
                        updateBoard(b.toString(), numbers);
                        b.drawBoard();
                    } else if (resetButton.checkClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "New Puzzle\n";
                        r = rand() % 54 + 1;
                        cout << r << '\n';
                        for (int i = 0; i <= r; i++) {
                            getline(boards, line);
                        }
                        b = Board(line);
                        // Board b();
                        b.drawBoard();
                        updateBoard(b.toString(), numbers);
                    }
                    break;

                case sf::Event::MouseMoved:
                    // std::cout << "Mouse Moved: ";
                    // std::cout << "x = " << event.mouseMove.x << ", y = " << event.mouseMove.y << '\n';
                    solveButton.checkHover(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                    resetButton.checkHover(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
                    break;
                default:
                    break;
            }
        }
        //draw loop
        window.clear(sf::Color(0, 102, 255, 255));
        

        // window.draw(board);
        // for(int i = 0; i < 8; i++) {
        //     window.draw(verticalLines[i]);
        //     window.draw(horizontalLines[i]);
        // }
       
        window.draw(text);
        window.draw(b);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                // window.draw(board[i][j]);
                window.draw(numbers[i][j]);
            }
        }

        

        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);

        window.draw(solveButton);
        window.draw(resetButton);

        window.display();
    }

    return 0;
}

