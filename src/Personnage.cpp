#include "Personnage.h"

#include <iostream>

using namespace std;


Personnage::Personnage() :
    m_nom("Defaut"),
    m_vie(100),
    m_arme(NULL)
{
    m_arme = new Arme();
}

Personnage::Personnage(string nom) :
    m_nom(nom),
    m_vie(100),
    m_arme(NULL)
{
    m_arme = new Arme();
}

Personnage::Personnage(Personnage const& personnageACopier)
   : m_nom(personnageACopier.m_nom), m_vie(personnageACopier.m_vie)
{
    m_arme = new Arme(*(personnageACopier.m_arme));
}


Personnage::~Personnage()
{
    cout << "Personnage " << m_nom << " a ete detruit." << endl;
    delete m_arme;
}

void Personnage::attaquer(Personnage &cible) {
    cout << m_nom << " attaque " << cible.getNom() << endl;
    cible.recevoirDegats(m_arme->getDegats());
}

void Personnage::recevoirDegats(int degats) {
    cout << m_nom << " recoit " << degats << " degats." << endl;
    m_vie -= degats;
    if (m_vie<0)
        m_vie = 0;
}



string Personnage::getNom() const {
    return m_nom;
}

bool Personnage::isVivant() const {
    return m_vie > 0;
}

void Personnage::afficher(ostream &flux) const {
    flux << m_nom << " : " << endl;
    flux << "   vie : " << m_vie << endl;
    flux << "   arme : " << m_arme->getNom() << "[" << m_arme->getDegats() << "]" << endl;
}

void Personnage::sePresenter() const
{
    cout << "Je m'appelle " << m_nom << " et je suis un personnage." << endl;
}

ostream &operator<<( ostream &flux, Personnage const &p)
{
    p.afficher(flux) ;
    return flux;
}

Personnage &Personnage::operator=(Personnage const& personnageACopier) {
    if (this != &personnageACopier) {
        m_nom = personnageACopier.m_nom;
        m_vie = personnageACopier.m_vie;
        delete m_arme;
        m_arme = new Arme(*(personnageACopier.m_arme));
    }
    return *this;
}

Personnage const *Personnage::getAdresse() const
{
    return this;
}

void presenter(Personnage const &p) {
    p.sePresenter();
}
