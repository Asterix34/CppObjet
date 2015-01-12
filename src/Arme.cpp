#include <string>
using namespace std;

#include "Arme.h"

Arme::Arme() :
    m_nom("Vieille epee pourrie"),
    m_degats(5)
{
    //ctor
}

Arme::Arme(std::string nom, int degats) :
    m_nom(nom),
    m_degats(degats)
{
    //ctor
}

Arme::~Arme()
{
    //dtor
}

int Arme::getDegats() const {
    return m_degats;
}

string Arme::getNom() const {
    return m_nom;
}
