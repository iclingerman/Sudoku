#include <string>
#include <list>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Button : public sf::Drawable, public sf::Transformable {
    private: 
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::RectangleShape button;
        sf::Text label;
        sf::Color color;


        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            // std::cout << "Drawing Button\n";
            target.draw(button);
            target.draw(label);
        }
    
    public:
        Button(sf::Text label, sf::Vector2f pos, sf::Vector2f size, sf::Color color);
        void setPos(sf::Vector2f pos);
        void setLabel(sf::Text label);
        void setColor(sf::Color color);
        void checkHover(sf::Vector2f mousePos);
        bool checkClick(sf::Vector2f mousePos);
};