#ifndef PACMAN_SUBJECT_H
#define PACMAN_SUBJECT_H

#include <vector>
#include <memory>
#include "Observer.h"

namespace logic
{
    class Subject
    {
    public:
        virtual ~Subject() = default;
        void attach(std::shared_ptr<Observer> observer);
        [[nodiscard]] const std::vector<std::shared_ptr<Observer>>& getObservers() const;

    protected:
        void notify() const;
        void OnEvent(GameEvent event, int data) const;
    private:
        std::vector<std::shared_ptr<Observer>> observers;
    };
} // logic

#endif //PACMAN_SUBJECT_H