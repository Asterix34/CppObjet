#ifndef ARME_H
#define ARME_H

#include <string>

class Arme
{
    public:
        Arme();
        Arme(std::string nom, int degats);
        virtual ~Arme();
        int getDegats() const;
        std::string getNom() const;
    protected:
    private:
        std::string m_nom;
        int m_degats;
};

#endif // ARME_H
