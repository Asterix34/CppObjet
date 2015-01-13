#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <string>

#include "Arme.h"

class Personnage
{
    public:
        Personnage();
        Personnage(std::string nom);
        Personnage(Personnage const& personnageACopier);
        virtual ~Personnage();
        void attaquer(Personnage &cible);
        void recevoirDegats(int degats);
        void afficher(std::ostream &flux) const;
        bool isVivant() const;
        std::string getNom() const;
        Personnage const *getAdresse() const;
    protected:
    private:
        std::string m_nom;
        int m_vie;
        Arme *m_arme;
};

std::ostream &operator<<(std::ostream &flux, Personnage const &p);

#endif // PERSONNAGE_H
