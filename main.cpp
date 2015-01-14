#include <iostream>
using namespace std;

#include <vector>

#include "Guerrier.h"
#include "Mage.h"

int test1();
int test2();

int main() {

    enum MenuPrincipal { Quitter=0, CreerPersonnage=1, LancerJeu=2, Test1=3, Test2=4 };

    int saisie = -1;

    cout << "Bienvenue dans mon application console C++" << endl;

    do  {
        cout << "Veuillez saisir le numéro du menu..." << endl;
        cout << "1. Créer un personnage" << endl;
        cout << "2. Lancer le jeu" << endl;
        cout << "3. Lancer test1" << endl;
        cout << "4. Lancer test2" << endl;
        cout << "0. Quitter" << endl;
        cin  >> saisie;

        switch (saisie) {
            case CreerPersonnage:
                cout << "Not implemented" << endl;
                break;
            case LancerJeu:
                cout << "Not implemented" << endl;
                break;
            case Test1:
                test1();
                break;
            case Test2:
                test2();
                break;
        }

    } while (saisie != Quitter);

    cout << "A bientot !" << saisie << endl;

}








int test1()
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

int test2() {
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
