#include "Subject.h"

namespace logic
{
    void Subject::attach(std::unique_ptr<Observer> observer)
    {
        observers.emplace_back(std::move(observer));
    }

    void Subject::notify() const
    {
        for(const auto& observer : observers)
        {
            observer->update();
        }
    }

    const std::vector<std::unique_ptr<Observer>>& Subject::getObservers() const {
        return observers;
    }

    void Subject::draw(Renderer& renderer) {
        if (!observers.empty()) {
            observers.at(0)->draw(renderer);
        }
    }
} // logic