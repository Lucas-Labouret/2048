#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Plateau;
typedef Plateau matrix;

Plateau plateauVide();
Plateau plateauInitial();
int tireDeuxOuQuatre();

matrix addTwoOrFour(matrix grid);
vector<int> getPossibleMoves(matrix grid);

Plateau deplacementGauche(Plateau plateau);
Plateau deplacementDroite(Plateau plateau);
Plateau deplacementHaut(Plateau plateau);
Plateau deplacementBas(Plateau plateau);
Plateau deplacement(Plateau plateau, int direction);

string dessine(Plateau g);
bool estTermine(Plateau plateau);
bool estGagnant(Plateau plateau);

void reset_rand(int seed, int iter);
