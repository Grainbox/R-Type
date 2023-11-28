/*
** EPITECH PROJECT, 2023
** client
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

    #include <SFML/Graphics.hpp>
    #include <iostream>

class Button {
    public:
        Button(std::string name, size_t x, size_t y, size_t w, size_t h, sf::RenderWindow *window, bool *events);
        ~Button();
        void draw();
        void handle_click();
        void handle_hover();

        sf::Text *text;
        sf::RectangleShape *rectangle;
        sf::Font *font;
        sf::RenderWindow *window;
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::Vector2i mouse;
        bool isOn = false;
        bool *event;
};

#endif /* !BUTTON_HPP_ */
