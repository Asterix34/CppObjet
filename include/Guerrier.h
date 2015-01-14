#ifndef GUERRIER_H
#define GUERRIER_H

#include <Personnage.h>


class Guerrier : public Personnage
{
    public:
        Guerrier();
        Guerrier(std::string nom);
        virtual ~Guerrier();
        void trancher(Personnage &cible);
        void sePresenter() const;
    protected:
    private:
};

#endif // GUERRIER_H
