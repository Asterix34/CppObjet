#ifndef OBJET_H
#define OBJET_H

#include <string>

class Objet
{
    public:
        Objet();
        Objet(std::string nom);
        virtual ~Objet();
        std::string getNom() const;
        static Objet* getRandomObjet();
    protected:
        std::string m_nom;
    private:

};

#endif // OBJET_H
