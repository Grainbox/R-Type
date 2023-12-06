/*
** EPITECH PROJECT, 2023
** B-CPP-500-REN-5-2-bsrtype-tom.daniel
** File description:
** Game
*/

#include "Game.hpp"

Game::Game()
{
    window.create(sf::VideoMode(800, 600), "My Game");

    this->initialize();
}

void Game::run()
{
    while (this->window.isOpen()) {
        this->processEvents();
        this->update();
        this->render();
    }
}

void Game::initialize()
{
    Entity button = this->r.spawnEntity();

    Position pos2(200, 200);
    Drawable draw2("assets/entity_2.png");

    this->r.addComponent<Position>(button, pos2);
    this->r.addComponent<Drawable>(button, draw2);

    Entity player = this->r.spawnEntity();

    Position pos(100, 0);
    Drawable draw("assets/entity_1.png");
    Controllable control;
    Velocity vel(0, 0);

    this->r.addComponent<Position>(player, pos);
    this->r.addComponent<Drawable>(player, draw);
    this->r.addComponent<Controllable>(player, control);
    this->r.addComponent<Velocity>(player, vel);

    this->r.killEntity(button);
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        Sparse_Array<Controllable> &controllables = r.getComponents<Controllable>();
        Sparse_Array<Velocity> &velocities = r.getComponents<Velocity>();
        system.control_system(controllables, velocities, event);
    }
}

void Game::update()
{
    Sparse_Array<Position> &positions = r.getComponents<Position>();
    Sparse_Array<Velocity> &velocities = r.getComponents<Velocity>();
    system.position_system(positions, velocities);
}

void Game::render()
{
    window.clear();

    Sparse_Array<Position> &positions = r.getComponents<Position>();
    Sparse_Array<Drawable> &drawables = r.getComponents<Drawable>();
    system.draw_system(positions, drawables, window);

    window.display();
}
