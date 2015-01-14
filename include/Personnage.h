#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <string>

#include "Arme.h"
#include "Coffre.h"

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
        void prendreObjet(Objet *o);
        void detruireObjet(Objet *o);
        void ouvrirInventaire();
    protected:
        std::string m_nom;
        int m_vie;
        Arme *m_arme;
        Coffre m_coffre;
    private:

    friend std::ostream &operator<<(std::ostream &flux, Personnage const &p);

};



void presenter(Personnage const &p);

#endif // PERSONNAGE_H
