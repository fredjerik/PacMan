#include <iostream>
#include <thread>
#include <chrono>
#include "../src/Singleton/Stopwatch.h"

void test_basic_timing() {
    std::cout << "--- Testing Basic Timing ---" << std::endl;
    auto& watch = singleton::Stopwatch::get_instance();

    watch.reset();
    watch.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    watch.stop();

    std::cout << "Elapsed time after 100ms sleep: " << watch.elapsed_milliseconds() << "ms" << std::endl;
    if (!watch.is_running()) {
        std::cout << "Stopwatch is correctly reported as not running." << std::endl;
    }

    watch.reset();
    if (watch.elapsed_seconds() == 0) {
        std::cout << "Stopwatch reset successfully." << std::endl;
    }
    std::cout << std::endl;
}

void test_pause_resume() {
    std::cout << "--- Testing Pause and Resume ---" << std::endl;
    auto& watch = singleton::Stopwatch::get_instance();

    watch.reset();
    watch.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    watch.pause();
    std::cout << "Paused stopwatch." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // This time should not be counted
    watch.resume();
    std::cout << "Resumed stopwatch." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    watch.stop();

    std::cout << "Elapsed time after pausing for 500ms: " << watch.elapsed_milliseconds() << "ms" << std::endl;
    std::cout << "This should be around 100ms." << std::endl;
    std::cout << std::endl;
}

void test_fps_limiter() {
    std::cout << "--- Testing FPS Limiter ---" << std::endl;
    auto& watch = singleton::Stopwatch::get_instance();

    watch.reset();
    watch.set_target_fps(10);
    std::cout << "Target FPS set to: " << watch.get_target_fps() << std::endl;

    watch.start();
    for (int i = 0; i < 5; ++i) {
        float delta_time = watch.tick();
        std::cout << "Tick " << i + 1 << " - Delta time: " << delta_time << "s" << std::endl;
    }
    watch.stop();
    std::cout << std::endl;
}

int main() {
    std::cout << "--- Stopwatch Test Suite ---" << std::endl;

    test_basic_timing();
    test_pause_resume();
    test_fps_limiter();

    std::cout << "--- All tests complete ---" << std::endl;

    return 0;
}
