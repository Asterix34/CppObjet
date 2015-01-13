#include <iostream>
using namespace std;

#include "Personnage.h"

int main()
{
    cout << "RPG Combat" << endl;

    Personnage david("David"), goliath(david);

    cout << david << endl;
    cout << goliath << endl;

    david.attaquer(goliath);
    goliath.attaquer(david);
    david.attaquer(goliath);


    cout << david << endl;
    cout << goliath << endl;


    /*if (david == goliath)
        cout << "David == Goliath" << endl;*/

    return 0;
}
