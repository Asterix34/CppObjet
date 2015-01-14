#ifndef COFFRE_H
#define COFFRE_H

#include <vector>
#include "Objet.h"


class Coffre
{
    public:
        Coffre();
        Coffre(unsigned int nbMax);
        virtual ~Coffre();
        void ouvrir();
        void ajouterObjet(Objet* o);
        std::vector<Objet*> m_objets;
    protected:
        //std::vector<Objet*> m_objets;
    private:
};

#endif // COFFRE_H
