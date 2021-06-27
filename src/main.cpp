#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello World!", sf::Style::Default, settings);

    sf::Font font;
    if(!font.loadFromFile("./data/SEGOEUI.TTF")) {
        std::cout << "Error loading font\n";
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello World!");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));

    sf::CircleShape circle(200.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(sf::Vector2f(window.getSize().x/2-200, window.getSize().y/2-200));
    // circle.setPointCount(1000);

    float radius = 200;
    bool growing = false;

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
                default:
                    break;
            }
        }
        //draw loop
        window.clear(sf::Color::White);
        
        if(radius == 0 && !growing) {
            growing = true;
        } else if(radius == 200 && growing) {
            growing = false;
        }

        if(!growing) {
            radius -= 0.25;
        } else {
            radius += 0.25;
        }
        
        circle.setRadius(radius);
        circle.setPosition(sf::Vector2f(window.getSize().x/2-radius, window.getSize().y/2-radius));
        window.draw(circle);
        window.draw(text);
        

        window.display();
    }

    return 0;
}