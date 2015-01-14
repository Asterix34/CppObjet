#ifndef MAGE_H
#define MAGE_H

#include <Personnage.h>


class Mage : public Personnage
{
    public:
        Mage();
        Mage(std::string nom);
        virtual ~Mage();
        void bruler(Personnage &cible);
        void sePresenter() const;
    protected:
    private:

};

#endif // MAGE_H
