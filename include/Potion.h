#ifndef POTION_H
#define POTION_H

#include <Objet.h>


class Potion : public Objet
{
    public:
        Potion();
        virtual ~Potion();
    protected:
    private:
        int m_vie;
};

#endif // POTION_H
