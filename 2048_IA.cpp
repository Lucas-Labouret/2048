#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <stdexcept>

#include "common.h"
#include "model.h"
#include "ai_player.h"

using namespace std;

int GRID_HEIGHT = 4;
int GRID_WIDTH  = 4;

tuple<int, matrix> readGrid(){
	int iter, score;
	ifstream f("configuration.txt");
	f >> iter >> score;

	string strGrid;
	f >> strGrid;

	matrix grid = {};
	vector<int> line = {};
	string num = "";
	for (int i = 0; i < strGrid.size(); i++){
		if (strGrid[i] == ';'){ 
			grid.push_back(line);
			line = {};
		}
		else if (strGrid[i] == ','){
			line.push_back(stoi(num));
			num = "";
		}
		else {
			num += strGrid[i];
		}
	}
	grid.push_back({score});

	return make_tuple(iter, grid);
}


string mapMove(int move){
	switch( move ){
		case HAUT   :
			return "H";
			break;
		case BAS    :
			return "B";
			break;
		case DROITE :
			return "D";
			break;
		case GAUCHE :
			return "G";
			break;
		default:
			return "B";
			break;
	}
}


int main(){
	ofstream f("mouvement.txt");
	f << "GWN" << endl;

	int previousIter = -1;
	int iter;
	matrix grid;
	do{
		do{
			tuple<int, matrix> tmp = readGrid();
			iter = get<0>(tmp);
			grid = get<1>(tmp);
		} while (iter == previousIter);

		int move = aiMain(grid);
		f << iter << " " << mapMove(move) << endl;

	} while (not estTermine(grid));
	return 0;
}