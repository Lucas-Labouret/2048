#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Plateau;
typedef Plateau matrix;

const int GAUCHE = 7;
const int DROITE = 4;
const int HAUT = 8;
const int BAS = 2;
const int UNDO = 1;
const int EXIT = 0;

const int GRID_HEIGHT = 4;
const int GRID_WIDTH = 4;

string operator * (string str, unsigned int n);

Plateau plateauVide();
Plateau plateauInitial();
int tireDeuxOuQuatre();

Plateau deplacementGauche(Plateau plateau);
Plateau deplacementDroite(Plateau plateau);
Plateau deplacementHaut(Plateau plateau);
Plateau deplacementBas(Plateau plateau);
Plateau deplacement(Plateau plateau, int direction);

string dessine(Plateau g);
bool estTermine(Plateau plateau);
bool estGagnant(Plateau plateau);
int score(Plateau plateau);

void reset_rand(float seed, int iter);
