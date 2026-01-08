#ifndef PACMAN_RANDOM_H
#define PACMAN_RANDOM_H

#pragma once

#include <random>

namespace singleton
{
    class Random {
    public:
        static Random& get_instance();

        // Delete copy constructor and assignment operator
        Random(const Random&) = delete;
        Random& operator=(const Random&) = delete;

        // Get random integer between min and max (inclusive)
        int get_int(int min, int max);

        // Get random float between min and max
        float get_float(float min, float max);

    private:
        Random(); // Private constructor

        std::mt19937 generator;
    };
} // singleton

#endif //PACMAN_RANDOM_H