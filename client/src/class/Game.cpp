/*
** EPITECH PROJECT, 2023
** client
** File description:
** Game
*/

#include "../../includes/class/Game.hpp"

// gerent tout les evenement du au component
void Game::event_factory()
{
    if (event_handler["Play"]) {
        std::cout << "play click" << std::endl;
        event_handler["Play"] = false;
    }
    if (event_handler["Setting"]) {
        std::cout << "Setting click" << std::endl;
        event_handler["Setting"] = false;
    }
    if (event_handler["Quit"]) {
        window->close();
    }
}

// Crée un component
void Game::init_component()
{
    event_handler["Play"] = false;
    Button play_button ("Play", width * 3, height * 20, width * 25, height * 10, window, &event_handler["Play"]);
    button.push_back(play_button);
    event_handler["Setting"] = false;
    Button settings_button ("Setting", width * 3, height * 40, width * 25, height * 10, window, &event_handler["Setting"]);
    button.push_back(settings_button);
    event_handler["Quit"] = false;
    Button quit_button ("Quit", width * 3, height * 60, width * 25, height * 10, window, &event_handler["Quit"]);
    button.push_back(quit_button);
}

// init toute les valeur d'affichage
Game::Game()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    height = (desktop.height/100)/2;
    width = (desktop.width/100)/2;
    window = new sf::RenderWindow(desktop, "R-Type", sf::Style::Resize | sf::Style::Close);
    font = new sf::Font;
    font->loadFromFile("./asset/Pixelify_Sans/PixelifySans-VariableFont_wght.ttf");
    title = new sf::Text;
    title->setFont(*font);
    title->setString("R-Type");
    title->setCharacterSize(100);
    title->setFillColor(sf::Color::Black);
    title->setPosition(3 * width, 2 * height);
    init_component();
}

void Game::start()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;

                default:
                    break;
            }
        }
        window->clear(sf::Color::White);
        window->draw(*title);
        for (auto it : button)
            it.draw();
        event_factory();
        window->display();
    }
}

Game::~Game()
{
    delete window;
    delete font;
    delete title;
}
