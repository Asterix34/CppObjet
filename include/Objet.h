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
        static Objet* getRandomObjet(); // génère un objet aléatoire
        void menuAction(); // TODO remplir fonction
    protected:
        std::string m_nom;
    private:

};

#endif // OBJET_H
