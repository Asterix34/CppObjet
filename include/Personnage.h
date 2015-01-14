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
        //void afficher(std::ostream &flux) const;
        virtual void sePresenter() const;
        bool isVivant() const;
        std::string getNom() const;
        Personnage const *getAdresse() const; // demo de this
        Personnage& operator=(Personnage const& personnageACopier); // opérateur d'assignation
        void prendreObjet(Objet *o); // ramasser un objet
        void detruireObjet(Objet *o); // detruire un objet
        void ouvrirInventaire(); // ouvrir l'inventaire
        // void equiperArme(Arme *o); // équiper une arme
    protected:
        std::string m_nom;
        int m_vie;
        Arme *m_arme; // arme
        Coffre m_coffre; // inventaire du personnage
    private:

    // surcharge de l'opérateur << pour l'affichage dans un flux
    friend std::ostream &operator<<(std::ostream &flux, Personnage const &p);

};

#endif // PERSONNAGE_H
