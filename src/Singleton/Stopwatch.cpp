#include "Stopwatch.h"

#include <thread>

namespace singleton
{
    Stopwatch::Stopwatch() {
        last_frame_time = std::chrono::steady_clock::now();
    }

    Stopwatch& Stopwatch::get_instance() {
        static Stopwatch instance;
        return instance;
    }

    void Stopwatch::start() {
        if (!running) {
            start_time = std::chrono::steady_clock::now();
            running = true;
            paused = false; // Make sure it's not paused when starting
        }
    }

    void Stopwatch::stop() {
        if (running) {
            end_time = std::chrono::steady_clock::now();
            running = false;
        }
    }

    void Stopwatch::reset() {
        running = false;
        paused = false;
        start_time = std::chrono::steady_clock::time_point{};
        end_time = std::chrono::steady_clock::time_point{};
        pause_time = std::chrono::steady_clock::time_point{};
    }

    float Stopwatch::elapsed_seconds() const {
        if (!running && end_time == std::chrono::steady_clock::time_point{}) {
            return 0.0f;
        }
        auto end = running ? std::chrono::steady_clock::now() : end_time;
        if (paused) {
            end = pause_time;
        }
        auto duration = std::chrono::duration_cast<std::chrono::duration<float>>(end - start_time);
        return duration.count();
    }

    float Stopwatch::elapsed_milliseconds() const {
        return elapsed_seconds() * 1000.0f;
    }

    bool Stopwatch::is_running() const {
        return running;
    }

    void Stopwatch::set_target_fps(float fps) {
        if (fps > 0) {
            target_fps = fps;
        }
    }



    float Stopwatch ::tick() {
        auto current_time = std::chrono::steady_clock::now();

        // Calculate how long this frame took
        auto frame_time = std::chrono::duration_cast<std::chrono::duration<float>>(
            current_time - last_frame_time);
        float delta_time = frame_time.count();

        // Sleep to maintain target frame rate if not paused
        if (!paused && target_fps > 0) {
            float target_frame_time = 1.0f / target_fps;

            // If we finished the frame too quickly, sleep the remaining time
            if (delta_time < target_frame_time) {
                float sleep_time_seconds = target_frame_time - delta_time;
                auto sleep_duration = std::chrono::duration<float>(sleep_time_seconds);

                std::this_thread::sleep_for(sleep_duration);

                // Update current time after sleep
                current_time = std::chrono::steady_clock::now();
                frame_time = std::chrono::duration_cast<std::chrono::duration<float>>(
                    current_time - last_frame_time);
                delta_time = frame_time.count();
            }
        }

        last_frame_time = current_time;
        return delta_time;
    }

    void Stopwatch::pause() {
        if (running && !paused) {
            paused = true;
            pause_time = std::chrono::steady_clock::now();
        }
    }

    void Stopwatch::resume() {
        if (running && paused) {
            auto paused_duration = std::chrono::steady_clock::now() - pause_time;
            start_time += paused_duration;
            paused = false;
            // Update last frame time to avoid large delta after resume
            last_frame_time = std::chrono::steady_clock::now();
        }
    }
} // singleton