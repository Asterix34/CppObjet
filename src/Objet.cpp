#include "Objet.h"

#include <iostream>
#include <string>

using namespace std;

Objet::Objet() : m_nom("Objet")
{
    //ctor
}

Objet::Objet(string nom) : m_nom(nom)
{
    //ctor
}

Objet::~Objet()
{
    cout << "Objet " << m_nom << " a ete detruit." << endl;
}

string Objet::getNom() const {
    return m_nom;
}

Objet* Objet::getRandomObjet() {
    return new Objet("Random Objet");
}

void menuAction() {
// TODO remplir méthode
// TODO créer classe menu contextuel
}
