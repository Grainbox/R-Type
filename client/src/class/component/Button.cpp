/*
** EPITECH PROJECT, 2023
** client
** File description:
** Button
*/

#include "../../../includes/class/component/Button.hpp"

// name, pos, size
Button::Button(std::string name, size_t x, size_t y, size_t w, size_t h, sf::RenderWindow *windows, bool *events)
{
    size = {static_cast<float>(w), static_cast<float>(h)};
    pos = {static_cast<float>(x), static_cast<float>(y)};

    rectangle = new sf::RectangleShape(size);
    rectangle->setPosition(pos);
    rectangle->setFillColor(sf::Color::Black);

    font = new sf::Font;
    font->loadFromFile("./asset/Pixelify_Sans/PixelifySans-VariableFont_wght.ttf");

    text = new sf::Text();
    text->setFont(*font);
    text->setString(name);
    text->setCharacterSize(size.y/2);
    text->setFillColor(sf::Color::White);
    text->setPosition((pos.x + size.x / 3) - (size.y/2)/2, (pos.y + size.y / 4.5));

    window = windows;
    event = events;
}

Button::~Button()
{
}

void Button::handle_click ()
{
    if (isOn && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        *event = true;
}

void Button::handle_hover ()
{
    if (mouse.x < pos.x || mouse.x > pos.x + size.x) return;
    if (mouse.y < pos.y || mouse.y > pos.y + size.y) return;
    isOn = true;
    // animation function here()
}

void Button::draw ()
{
    isOn = false;
    mouse = sf::Mouse::getPosition(*window);
    handle_hover();
    handle_click();
    window->draw(*rectangle);
    window->draw(*text);
}
