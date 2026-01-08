#include "Random.h"

namespace singleton
{
    Random::Random() {
        // Initialize with random device
        std::random_device rd;
        generator.seed(rd());
    }

    Random& Random::get_instance() {
        static Random instance;
        return instance;
    }

    int Random::get_int(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(generator);
    }

    float Random::get_float(float min, float max) {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(generator);
    }
} // singleton