#ifndef PACMAN_STOPWATCH_H
#define PACMAN_STOPWATCH_H

#pragma once

#include <chrono>

namespace singleton
{
    class Stopwatch {
    public:
        static Stopwatch& get_instance();

        Stopwatch(const Stopwatch&) = delete;
        Stopwatch& operator=(const Stopwatch&) = delete;

        void start();
        void stop();
        void reset();
        [[nodiscard]] float elapsed_seconds() const;
        [[nodiscard]] float elapsed_milliseconds() const;
        [[nodiscard]] bool is_running() const;

        void set_target_fps(float fps);
        [[nodiscard]] float get_target_fps() const { return target_fps; }
        float tick();
        void pause();
        void resume();

    private:
        Stopwatch();

        std::chrono::steady_clock::time_point start_time;
        std::chrono::steady_clock::time_point end_time;
        std::chrono::steady_clock::time_point last_frame_time;
        std::chrono::steady_clock::time_point pause_time;
        bool running = false;

        float target_fps = 60.0f;
        bool paused = false;
    };
}

#endif