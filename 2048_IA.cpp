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

tuple<int, matrix> readGrid(int previousIter){
	int iter;
	matrix grid = {};
	bool errorFlag = false;
	do{
		int score;
		ifstream f;
		while (true){
			f.open("configuration.txt");
			if (f >> iter >> score){
				if (previousIter < iter){ break; }
			}
			f.close();
		}
		string strGrid;
		vector<int> line = {};
		string num = "";
		for (int n = 0; n < 4; n++){
			if (f >> strGrid){
				for (int i = 0; i < strGrid.size(); i++){
					if (strGrid[i] == ';'){
						line.push_back(stoi(num));
						num = "";
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
			} else {
				errorFlag = true;
			}
		}
		grid.push_back({score});
		f.close();
	} while (errorFlag);

	return make_tuple(iter, grid);
}


string mapMove(int move){
	if (move == HAUT  ) {
		return "H";
	}
	if (move == BAS   ) {
		return "B";
	}
	if (move == DROITE) {
		return "D";
	}
	if (move == GAUCHE) {
		return "G";
	}
	return "B";
}


int main(){
	ofstream f("mouvements.txt");
	f << "GWN" << endl;

	int previousIter = -1;
	int iter;
	int move;
	matrix grid;
	while (true){
		tuple<int, matrix> tmp = readGrid(previousIter);
		iter = get<0>(tmp);
		grid = get<1>(tmp);

		if (estTermine(grid)){ break; }

		move = aiMain(grid);
		cout << dessine(grid) << endl;
		f << iter << " " << mapMove(move) << endl;
		previousIter = iter;
	}
	return 0;
}