#ifndef CONTAINER_H
#define CONTAINER_H

#include "main.hpp"

class Container
{
    public:
        int size; // maximum number capacity - 0 for unlimited
        TCODList<Unit *> inventory;

        Container(int size);
        virtual ~Container();

        bool add(Unit *unit);
        void remove(Unit *unit);
    protected:
    private:
};

#endif // CONTAINER_H
