#include <vector>
#include <ncurses.h>

using namespace std;

const int KEY_ENT =  10;
const int KEY_R   = 114;
const int KEY_S   = 115;
const int KEY_C   =  99;

const vector<int> VALID_KEYS = {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_BACKSPACE, KEY_ENT, KEY_R, KEY_S, KEY_C};

const int Y_MARGIN = 2;
const int X_MARGIN = 2;

typedef vector<vector<int>> matrix;

/**Configure la fenetre ncurses
**/
void startScreen();

/**Ferme la fenetre ncurses
**/
void endScreen();

/**Rafraichit l'écran
**/
void refreshScreen();

/**Demande a l'utilisateur de saisir une action a effectuer
**/
int getUserInput();

/**Affiche le jeu dans la console
 * @param grid le plateau
**/
void draw(matrix grid);

/**Indique que la partie a été remportée
**/
void drawWin();

/**Indique que la partie a été sauvergrdé
**/
void drawSave();

/**Indique que le mouvement demandé n'est pas valide
**/
void invalidMove();

/**Indique que la partie ne peut pas être chargée
 * @param message le message à afficher
**/
void cannotLoad(const char* message);

/**Indique que le mouvement demandé est impossible
**/
void cannotMove();

/**Indique que la partie est terminée
**/
bool drawEnd();
