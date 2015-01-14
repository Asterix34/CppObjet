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
        void ouvrir(); // permet d'ouvrir un coffre pour parcourir les objets
        void ajouterObjet(Objet* o); // ajoute un objet au coffre
        void enleveObjet(Objet* o);
        std::vector<Objet*> m_objets; // liste d'objets TODO : privé
    protected:
        //std::vector<Objet*> m_objets;
    private:

    friend std::ostream &operator<<( std::ostream &flux, Coffre const &c);
};

#endif // COFFRE_H
