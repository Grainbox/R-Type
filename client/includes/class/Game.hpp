/*
** EPITECH PROJECT, 2023
** client
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

    #include <SFML/Graphics.hpp>
    #include <map>
    #include <iostream>
    #include "component/Button.hpp"

class Game {
    public:
        Game();
        ~Game();
        void start();
    protected:
    private:
        void init_component();
        void event_factory();
        sf::RenderWindow *window;
        std::vector<Button> button;
        sf::Font *font;
        sf::Text *title;
        size_t height;
        size_t width;
        std::map<std::string, bool> event_handler;
};

#endif /* !GAME_HPP_ */

