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


    friend std::ostream &operator<<(std::ostream &flux, Arme const &a);
};

#endif // ARME_H
