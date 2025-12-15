#ifndef PACMAN_OBSERVER_H
#define PACMAN_OBSERVER_H

#include <vector>
#include <memory>

namespace view {

    class Observer {
    public:
        virtual ~Observer() = default;
        virtual void update() = 0;
    };

    class Subject {
    private:
        std::vector<std::weak_ptr<Observer>> observers;

    public:
        virtual ~Subject() = default;

        void addObserver(std::shared_ptr<Observer> observer) {
            observers.push_back(observer);
        }

        void notify() {
            for (const auto& obs_weak : observers) {
                if (auto obs = obs_weak.lock()) {
                    obs->update();
                }
            }
        }
    };

} 

#endif //PACMAN_OBSERVER_H
