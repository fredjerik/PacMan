#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H

#pragma once

#include <chrono>

namespace singleton
{
    class Stopwatch {
    public:
        static Stopwatch& get_instance();

        // Delete copy constructor and assignment operator
        Stopwatch(const Stopwatch&) = delete;
        Stopwatch& operator=(const Stopwatch&) = delete;

        // Core functionality
        void start();
        void stop();
        void reset();
        float elapsed_seconds() const;
        float elapsed_milliseconds() const;
        bool is_running() const;

        // Frame rate control
        void set_target_fps(float fps);
        float get_target_fps() const { return target_fps; }
        float tick();  // Sleeps to maintain frame rate, returns delta time
        void pause();
        void resume();

    private:
        Stopwatch();  // Private constructor

        // Timing members
        std::chrono::steady_clock::time_point start_time;
        std::chrono::steady_clock::time_point end_time;
        std::chrono::steady_clock::time_point last_frame_time;
        std::chrono::steady_clock::time_point pause_time;
        bool running = false;

        // Frame rate control members
        float target_fps = 60.0f;
        bool paused = false;
    };
} // singleton

#endif //PACMAN_STOPWATCH_H