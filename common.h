#include <iostream>

using namespace std;

typedef vector<vector<int>> matrix;

const int GAUCHE = 7;
const int DROITE = 4;
const int HAUT = 8;
const int BAS = 2;
const int UNDO = 1;
const int EXIT = 0;
const int RESTART = 3;

const int GRID_HEIGHT = 4;
const int GRID_WIDTH = 4;

string operator * (string str, unsigned int n);
