#ifndef ARME_H
#define ARME_H

#include <Objet.h>

#include <string>

class Arme : public Objet
{
    public:
        Arme();
        Arme(std::string nom, int degats);
        virtual ~Arme();
        int getDegats() const;
        std::string getNom() const;
    protected:
    private:
        int m_degats;


    friend std::ostream &operator<<(std::ostream &flux, Arme const &a);
};

#endif // ARME_H
