#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "pacman.h"
#include "wall.h"
#include "consumable.h"
#include <iostream>
using namespace std;

class game {
public:
    game();
    ~game();

    void run();             // Main game loop
    void handle_events();   // SFML events
    void handle_input();    // Keyboard state
    void update(float& delta_time);  // Game logic
    void render();          // Drawing

private:
    sf::RenderWindow window_;
    sf::Clock clock_;

    // Entities
    pacman* pacman_;
    vector<dynamic_entity*> dynamic_entities;
    vector<wall*> walls_;
    vector<consumable*> consumables_;

    // Game state
    bool running_ = true;
    int score_ = 0;
    int level_ = 1;
};


#endif //PACMAN_GAME_H