#include "Guerrier.h"

#include <iostream>

using namespace std;

Guerrier::Guerrier() : Personnage()
{
    //ctor
}

Guerrier::Guerrier(string nom) : Personnage(nom)
{

}

Guerrier::~Guerrier()
{
    cout << "Guerrier " << m_nom << " a ete detruit." << endl;
}

void Guerrier::trancher(Personnage &cible) {
    cout << m_nom << " tranche " << cible.getNom() << endl;
    cible.recevoirDegats(m_arme->getDegats()*1.5);
}

void Guerrier::sePresenter() const
{
    Personnage::sePresenter();
    cout << "JE SUIS UN GUERRIER !!!" << endl;
}
