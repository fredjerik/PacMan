#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

struct position
{
    double x;
    double y;
};
class entity
{
public:
    entity();
    ~entity();

    inline void set_position(position& pos){position = pos;}
    inline position get_position() const {return position;}
private:
    position position;

};


#endif //PACMAN_ENTITY_H