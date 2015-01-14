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
        virtual void sePresenter() const;
        bool isVivant() const;
        std::string getNom() const;
        Personnage const *getAdresse() const;
        Personnage& operator=(Personnage const& personnageACopier);
    protected:
        std::string m_nom;
        int m_vie;
        Arme *m_arme;
    private:

};

std::ostream &operator<<(std::ostream &flux, Personnage const &p);

void presenter(Personnage const &p);

#endif // PERSONNAGE_H
