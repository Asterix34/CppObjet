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
        static Objet* getRandomObjet(); // g�n�re un objet al�atoire
        void menuAction(); // TODO remplir fonction
    protected:
        std::string m_nom;
    private:

};

#endif // OBJET_H
