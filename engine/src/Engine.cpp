/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(Registry *r)
{
    this->r = r;
    window.create(sf::VideoMode(800, 600), "My Engine");
}

void Engine::run()
{
    while (this->window.isOpen()) {
        this->processEvents();
        this->update();
        this->render();
    }
}

void Engine::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        system.control_system(*r, event);
    }
}

void Engine::update()
{
    system.position_system(*r);
}

void Engine::render()
{
    window.clear();

    system.draw_system(*r, window);

    window.display();
}
