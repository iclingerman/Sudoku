#include <string>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Button.h"


Button::Button(sf::Text label, sf::Vector2f pos, sf::Vector2f size, sf::Color color) {
    this->label = label;
    this->pos = pos;
    this->size = size;
    this->color = color;
    this->button = sf::RectangleShape(this->size);

    this->label.setPosition(this->pos);
    this->label.setFillColor(sf::Color::Black);
    this->button.setPosition(this->pos);
    this->button.setFillColor(this->color);
    this->button.setOutlineColor(sf::Color::Black);
    this->button.setOutlineThickness(3.0);
    
    
}
void Button::setPos(sf::Vector2f pos) {
    this->pos = pos;
    this->label.setPosition(this->pos);
    this->button.setPosition(this->pos);

}
void Button::setLabel(sf::Text label) {
    this->label = label;
}
void Button::setColor(sf::Color color) {
    this->color = color;
    this->button.setFillColor(this->color);
}

void Button::checkHover(sf::Vector2f mousePos) {
    if (mousePos.x >= this->pos.x && mousePos.x < this->pos.x+this->size.x && mousePos.y > this->pos.y && mousePos.y < this->pos.y+this->size.y) {
        // std::cout << "Mouse hovering\n";
        this->color = sf::Color::Green;
    } else {
        this->color = sf::Color::White;
    }

    this->button.setFillColor(this->color);
}

bool Button::checkClick(sf::Vector2f mousePos) {
    if (mousePos.x >= this->pos.x && mousePos.x < this->pos.x+this->size.x && mousePos.y > this->pos.y && mousePos.y < this->pos.y+this->size.y) {
        std::cout << "Button Clicked\n";
        return true;
    } else {
        std::cout << "Button Not Clicked\n";
        return false;
    }
}

