#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H

#include <iostream>
#include <memory>
#include <vector>

#include "../../Logic/Patterns/Observer.h"

namespace logic
{
    class Score: public Observer
    {
    public:
        Score(int global_highscore = 0, int personal_best = 0, int lives = 3)
            : global_highscore(global_highscore), personal_best(personal_best), pacman_lives(lives)
        {
            current_score = 0;
        }

        int get_score(){ return current_score; }
        int get_lives() { return pacman_lives; }
        void set_lives(int lives) { pacman_lives = lives; }

        void update() override
        {
        }

        void onGameEvent(GameEvent event, int data) override
        {
            if (event == GameEvent::CollectableCollected)
            {
                current_score += data;
                if (current_score > personal_best) {
                    personal_best = current_score;
                }
                if (current_score > global_highscore) {
                    global_highscore = current_score;
                }
            }
            else if (event == GameEvent::PacmanDied)
            {
                pacman_lives -= data;
            }
            else
            {
                std::cerr << "Incorrect Event!" << std::endl;
            }
        }

        void draw(Renderer& renderer) override;

    private:
        int global_highscore;
        int personal_best;
        int current_score;
        int pacman_lives;
    };
} // logic

#endif //PACMAN_SCORE_H