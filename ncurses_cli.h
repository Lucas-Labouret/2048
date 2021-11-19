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

void startScreen();
void endScreen();

int getUserInput();

void draw(matrix grid, int sc);
void drawWin();
void drawSave();
void invalidMove();
void cannotLoad();
void cannotMove();
bool drawEnd();
