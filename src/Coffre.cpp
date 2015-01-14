#include "Coffre.h"
#include "Objet.h"

#include <ctime> // Obligatoire
#include <cstdlib> // Obligatoire
#include <iostream>

using namespace std;

#include "Personnage.h"

extern Personnage *joueur;

Coffre::Coffre()
{
}

Coffre::Coffre(unsigned int nbMax)
{
    srand(time(0));
    unsigned int nbAleatoire = rand() % nbMax;
    for (unsigned int i(0); i<nbAleatoire; i++) {
        //objets.push_back(Objet::getRandomObjet());
        m_objets.push_back(new Objet("Random Objet"));
    }
}

Coffre::~Coffre()
{
    for (unsigned int i(0); i<m_objets.size(); i++) {
        delete m_objets[i];
        m_objets[i] = 0;
    }
}

void Coffre::ouvrir()
{
    enum MenuCoffre { Quitter=0 };

    int saisie = -1;

    cout << "Vous avez ouvert le coffre" << endl;

    do  {
        cout << "Veuillez saisir le numéro de l'objet a ramasser..." << endl;
        for (unsigned int i=0; i<m_objets.size(); i++) {
            cout << i+1 <<". " << m_objets[i]->getNom() << endl;
        }

        cout << "0. Quitter" << endl;
        cin  >> saisie;
        if (saisie>0&&saisie<=m_objets.size()) {
            joueur->prendreObjet(m_objets[saisie-1]);
            m_objets.erase(m_objets.begin()+saisie-1);
        }

    } while (saisie != Quitter);
}

void Coffre::ajouterObjet(Objet* o) {
    m_objets.push_back(o);
}
