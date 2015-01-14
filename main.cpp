#include <iostream>
using namespace std;

#include <vector>

#include "Guerrier.h"
#include "Mage.h"
#include "Coffre.h"
#include "Objet.h"

// prototpyes du main |TODO: classer dans des classes
int test1();
int test2();
int test3();
void creerPersonnage();
void lancerJeu();

// variables globales
Personnage *joueur;


int main() {

    enum MenuPrincipal { Quitter=0, CreerPersonnage=1, LancerJeu=2, Test1=3, Test2=4, Test3 };

    int saisie = -1;

    cout << "Bienvenue dans mon RogueLike" << endl;

    do  {
        cout << "Veuillez saisir le numéro du menu..." << endl;
        cout << "1. Créer un personnage" << endl;
        cout << "2. Lancer le jeu" << endl;
        /*cout << "3. Lancer test1" << endl;
        cout << "4. Lancer test2" << endl;
        cout << "4. Lancer test3" << endl;*/
        cout << "0. Quitter" << endl;
        cin  >> saisie;

        switch (saisie) {
            case CreerPersonnage:
                creerPersonnage();
                break;
            case LancerJeu:
                lancerJeu();
                break;
            case Test1:
                test1();
                break;
            case Test2:
                test2();
                break;
            case Test3:
                test3();
                break;
        }

    } while (saisie != Quitter);

    cout << "A bientot !" << saisie << endl;

}

void creerPersonnage() {
    cout << "Veuillez saisir le nom du personnage" << endl;
    string nom;
    cin >> nom;
    joueur = new Personnage(nom);

}

void lancerJeu() {
    cout << "Le jeu commence..." << endl;

    cout << "Creation d'un coffre rempli d'objets..." << endl;
    Coffre coffre(10);

    enum MenuJeu { Quitter=0, OuvrirCoffre=1, OuvrirInventaire=2 };

    int saisie = -1;

    cout << "Bienvenue dans mon RogueLike" << endl;

    do  {
        cout << "Veuillez saisir le numéro de l'action..." << endl;
        cout << "1. Ouvrir le coffre" << endl;
        cout << "2. Ouvrir mon inventaire" << endl;
        cout << "0. Quitter" << endl;
        cin  >> saisie;
        switch (saisie) {
            case OuvrirCoffre:
                coffre.ouvrir();
                break;
            case OuvrirInventaire:
                joueur->ouvrirInventaire();
                break;
        }

    } while (saisie != Quitter);

    cout << "Le jeu est termine..." << endl;
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

int test3() {
    Objet* o = Objet::getRandomObjet();
    //Objet::getRandomObjet();
    cout << o << endl;

    return 0;
}
