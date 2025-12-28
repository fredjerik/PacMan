#include "Subject.h"

#include <iostream>

namespace logic
{
    void Subject::attach(std::shared_ptr<Observer> observer)
    {
        observers.emplace_back(std::move(observer));
    }

    void Subject::notify() const {
        for(const auto& observer : observers) {
            observer->update();
        }
    }

    void Subject::OnEvent(GameEvent event, int data = 0) const {
        for(const auto& observer : observers) {
            observer->onGameEvent(event, data);
        }
    }

    const std::vector<std::shared_ptr<Observer>>& Subject::getObservers() const {
        return observers;
    }
} // logic