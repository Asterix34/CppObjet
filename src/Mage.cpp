#include "Mage.h"

#include <iostream>

using namespace std;

Mage::Mage()
{
    //ctor
}

Mage::Mage(string nom) : Personnage(nom)
{
    m_vie = 80;
}

Mage::~Mage()
{
    cout << "Mage " << m_nom << " a ete detruit." << endl;
}

void Mage::bruler(Personnage &cible) {
    cout << m_nom << " brule " << cible.getNom() << endl;
    cible.recevoirDegats(m_arme->getDegats()*2);
}

void Mage::sePresenter() const
{
    Personnage::sePresenter();
    cout << "Je suis le plus grand des mages." << endl;
}
