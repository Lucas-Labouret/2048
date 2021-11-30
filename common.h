#include <iostream>

using namespace std;

typedef vector<vector<int>> matrix;

const int GAUCHE  = 0;
const int DROITE  = 1;
const int HAUT    = 2;
const int BAS     = 3;
const int UNDO    = 4;
const int EXIT    = 5;
const int RESTART = 6;
const int SAVE    = 7;
const int LOAD    = 8;

const  int HUMAN = 0;
const  int AI    = 1;
extern int PLAYER;

extern int GRID_HEIGHT;
extern int GRID_WIDTH;

string operator * (string str, unsigned int n);
