#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Plateau;

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
