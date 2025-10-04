#include "game.h"
#include <SFML/Graphics.hpp>

game::game()
    : window_({1800, 1000}, "Pac-Man Game")
{
    pacman_ = new pacman();
    dynamic_entities.push_back(pacman_);

    // TODO: Initialize walls, consumables, ghosts
    // walls_.push_back(new wall());
    // consumables_.push_back(new consumable());
}

game::~game()
{
    for (auto* entity : dynamic_entities) {
        delete entity;
    }

    for (auto* wall : walls_) {
        delete wall;
    }

    for (auto* consumable : consumables_) {
        delete consumable;
    }
}

void game::run()
{
    while (window_.isOpen())
    {
        float delta_time = clock_.restart().asSeconds();

        handle_events();    // Window events (close, resize, etc.)
        handle_input();     // Keyboard input (ZQSD, Escape)
        update(delta_time); // Game logic updates
        render();           // Draw everything
    }
}

void game::handle_events()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();

        // TODO: Add other event handling (resize, focus, etc.)
    }
}

void game::handle_input() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        pacman_->set_direction(direction::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        pacman_->set_direction(direction::Down);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        pacman_->set_direction(direction::Left);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        pacman_->set_direction(direction::Right);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window_.close();
    }
}

void game::update(float& delta_time)
{
    // Update all dynamic entities (pacman + future ghosts)
    for (auto* entity : dynamic_entities) {
        entity->update(delta_time);
    }

    // TODO: Add collision detection
    // TODO: Add consumable collection
    // TODO: Add game state updates (score, lives, level progression)
}

void game::render()
{
    window_.clear();

    // Draw pacman
    window_.draw(pacman_->get_sprite());

    // TODO: Draw walls
    // for (auto* wall : walls_) {
    //     window_.draw(wall->get_sprite());
    // }

    // TODO: Draw consumables (dots, power pellets)
    // for (auto* consumable : consumables_) {
    //     window_.draw(consumable->get_sprite());
    // }

    // TODO: Draw ghosts (when added to dynamic_entities)

    window_.display();
}