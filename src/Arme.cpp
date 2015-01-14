#include <string>
#include <iostream>
using namespace std;

#include "Arme.h"

Arme::Arme() :
    Objet("Baton"),
    m_degats(1)
{
    //ctor
}

Arme::Arme(std::string nom, int degats) :
    Objet(nom),
    m_degats(degats)
{
    //ctor
}

Arme::~Arme()
{
    cout << "Arme " << m_nom << " a ete detruite." << endl;
}

int Arme::getDegats() const {
    return m_degats;
}

string Arme::getNom() const {
    return m_nom;
}

ostream &operator<<( ostream &flux, Arme const &a)
{
    //p.afficher(flux) ;
    flux << a.m_nom << "[" << a.m_degats << "]" << endl;
    return flux;
}
