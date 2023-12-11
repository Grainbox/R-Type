/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-rtype-tom.daniel
** File description:
** ClientEngine
*/

#include "client/ClientEngine.hpp"

ClientEngine::ClientEngine(Registry *r)
{
    this->r = r;
    this->window.create(sf::VideoMode(800, 600), "My Engine");
    this->run();
}

void ClientEngine::run()
{
    while (this->window.isOpen()) {
        this->processEvents();
        this->update();
        this->render();
    }
}

void ClientEngine::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        system.control_system(*r, event);
        system.click_system(*r, event, window);
    }
}

void ClientEngine::update()
{
    system.position_system(*r);
}

void ClientEngine::render()
{
    window.clear();

    system.draw_system(*r, window);
    system.draw_hitbox_system(*r, window);

    window.display();
}
