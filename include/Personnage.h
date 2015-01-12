#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <string>

#include "Arme.h"

class Personnage
{
    public:
        Personnage();
        Personnage(std::string nom);
        virtual ~Personnage();
        void attaquer(Personnage &cible);
        void recevoirDegats(int degats);
        void afficher(std::ostream &flux) const;
        bool isVivant() const;
        std::string getNom() const;
    protected:
    private:
        std::string m_nom;
        int m_vie;
        Arme arme;
};

std::ostream &operator<<(std::ostream &flux, Personnage const &p);

#endif // PERSONNAGE_H
