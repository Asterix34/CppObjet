#include "Personnage.h"

#include <iostream>

using namespace std;


Personnage::Personnage() :
    m_nom("Defaut"),
    m_vie(100)
{

}

Personnage::Personnage(string nom) :
    m_nom(nom),
    m_vie(100)
{
    //Personnage::Personnage();
}


Personnage::~Personnage()
{
    cout << "Personnage " << m_nom << " a ete detruit." << endl;
}

void Personnage::attaquer(Personnage &cible) {
    cout << m_nom << " attaque " << cible.getNom() << endl;
    cible.recevoirDegats(arme.getDegats());
}

void Personnage::recevoirDegats(int degats) {
    cout << m_nom << " recoit " << degats << " degats." << endl;
    m_vie -= degats;
    if (m_vie<0)
        m_vie = 0;
}

void Personnage::afficher(ostream &flux) const {
    flux << m_nom << " : " << endl;
    flux << "   vie : " << m_vie << endl;
    flux << "   arme : " << arme.getNom() << "[" << arme.getDegats() << "]" << endl;
}

string Personnage::getNom() const {
    return m_nom;
}

bool Personnage::isVivant() const {
    return m_vie > 0;
}

ostream &operator<<( ostream &flux, Personnage const &p)
{
    p.afficher(flux) ;
    return flux;
}
