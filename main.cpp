#include <iostream>
using namespace std;

#include "Personnage.h"

int main()
{
    cout << "RPG Combat" << endl;

    Personnage david("David"), goliath("Goliath");

    david.afficher();
    goliath.afficher();

    david.attaquer(goliath);
    goliath.attaquer(david);
    david.attaquer(goliath);


    david.afficher();
    goliath.afficher();


    /*if (david == goliath)
        cout << "David == Goliath" << endl;*/

    return 0;
}
