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
        void attach(std::unique_ptr<Observer> observer);
        const std::vector<std::unique_ptr<Observer>>& getObservers() const;
        virtual void draw(Renderer& renderer);


    protected:
        void notify() const;
    private:
        std::vector<std::unique_ptr<Observer>> observers;
    };
} // logic

#endif //PACMAN_SUBJECT_H