#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Plateau;
typedef Plateau matrix;

/** Construit le plateau de jeu 
 * @return un tableau 2D de dimension GRID_WIDTH*GRID_HEIGHT rempli de zéro
**/
Plateau plateauVide();

/** Cree le plateau de jeu initial et y ajoute deux tuiles indépendantes de valeur 2 ou 4
 * @return le plateau initial
**/
Plateau plateauInitial();

/** Liste les positions où il est possible de rajouter un 2 ou un 4
 * @param grid le plateau de jeu
 * @return un tableau de coordonnées de la forme {{y0, x0}, {y1,x1}, ...}
**/ 
matrix getValidPosition(matrix grid);

/** Tire aleatoirement 2 ou 4 avec une probabilité respctive de 0.9 et 0.1
 * @return 2 ou 4
**/
int tireDeuxOuQuatre();

/** Ajoute aleatoirement 2 ou 4 dans une case vide
 * @param grid le plateau de jeu
 * @return le plateau de jeu modifie
**/ 
matrix addTwoOrFour(matrix grid);

/** Verifie qu'un mouvement donne peut-etre effectue. (Il es alors dit "possible")
 * @param grid le plateau
 * @param move le mouvement a tester
 * return true si le mouvement est possible, false sinon
**/
bool checkMove(matrix grid, int move);

/** Verifie que chaque mouvement est possible
 * @param grid le plateau
 * @return une liste de mouvement possible
**/
vector<int> getPossibleMoves(matrix grid);


/** Effectue un deplacement vers la gauche
 * @plateau le plateau
 * @return le nouveau plateau
**/
Plateau deplacementGauche(Plateau plateau);

/** Effectue un deplacement vers la droite
 * @plateau le plateau
 * @return le nouveau plateau
**/
Plateau deplacementDroite(Plateau plateau);

/** Effectue un deplacement vers le haut
 * @plateau le plateau
 * @return le nouveau plateau
**/
Plateau deplacementHaut(Plateau plateau);

/** Effectue un deplacement vers le bas
 * @plateau le plateau
 * @return le nouveau plateau
**/
Plateau deplacementBas(Plateau plateau);

/**Déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 * @param grid le plateau
 * @param move le mouvement a effectuer
 * @return le nouveau plateau
**/
Plateau deplacement(Plateau plateau, int direction);

/** Construit une chaine de caracteres représentant le plateau
 * Cette fonction est obsolète, remplacée par la fonction draw() du fichier ncurses_cli.h
 * @param p le plateau
 * @return une chaine de caracteres représentant le plateau
**/
string dessine(Plateau p);

/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
**/
bool estTermine(Plateau plateau);

/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau);

/**Reproduit l'état de la fonction rand() après iter déplacements
 * @param seed la seed utiliser par la fonction srand() en début de partie
 * @param iter le nombre de déplacements à avoir été effectués
**/
void reset_rand(int seed, int iter);
