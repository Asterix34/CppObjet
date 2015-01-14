#include <iostream>
using namespace std;

#include <vector>

#include "Guerrier.h"
#include "Mage.h"

int main2()
{
    cout << "RPG Combat" << endl << endl ;

    cout << "Initialisation de michel et roger" << endl ;
    Personnage *michel(0), *roger(0);
    michel = new Personnage("Michel");
    roger = new Guerrier("Roger");

    cout << endl << "Presentation de michel et roger" << endl ;
    michel->sePresenter();
    roger->sePresenter();

    cout << endl << "delete de michel et roger" << endl ;
    delete roger;
    delete michel;





    Personnage david("David");
    Guerrier goliath("Goliath");
    Mage gandalf("Gandalf");


/*    cout << david << " ref: " << &david << endl;
    cout << goliath << " ref: " << &goliath << endl;*/

    cout << endl << "Presentation objet.sePresenter" << endl;
    david.sePresenter();
    goliath.sePresenter();

    cout << endl << "Presentation presenter(objet)" << endl;
    presenter(david);
    presenter(goliath);

    cout << endl;
    david.attaquer(goliath);
    goliath.trancher(david);
    david.attaquer(goliath);


    cout << david << endl;
    cout << goliath << endl;
    cout << gandalf << endl;


    /*if (david == goliath)
        cout << "David == Goliath" << endl;*/

    return 0;
}

int main() {
    cout << "RPG Combat - Collection" << endl << endl ;

    vector<Personnage*> liste;

    liste.push_back(new Personnage("David"));
    liste.push_back(new Guerrier("Goliath"));
    liste.push_back(new Mage("Gandalf"));

    cout << "Présentation des personnages dans la liste" << endl;

    for (int i = 0; i<liste.size(); i++) {
        liste[i]->sePresenter();
    }

    cout << endl << "Suppression des personnages dans la liste" << endl;
    for (int i = 0; i<liste.size(); i++) {
        delete liste[i];
        liste[i] = 0;
    }

    return 0;
}
