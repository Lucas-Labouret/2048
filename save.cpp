#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "common.h"
#include "model.h"
#include "save.h"

using namespace std;

void saveFile(int seed, vector<matrix> gridHistory){
	ofstream f("savefile.txt");
	f << GRID_HEIGHT << " " << GRID_WIDTH << endl;
	f << seed << endl;
	f << endl;
	for (auto grid: gridHistory){
		for (auto line: grid){
			for (auto cell: line){
				f << cell << " ";
			}
			f << endl;
		}
		f << endl;
	}
	f.close();
}

vector<matrix> loadFile(){
	ifstream f("savefile.txt");

	int height, width;
	f >> height >> width;
	if (not (height == GRID_HEIGHT and width == GRID_WIDTH)){
		throw ios_base::failure( "Les données de sauvegarde correspondent à une grille de " 
			                    +to_string(width)+ "x" + to_string(height)
			                    +", pas " + to_string(GRID_WIDTH) + "x" + to_string(GRID_HEIGHT));
	}

	int seed;
	f >> seed;

	vector<matrix> gridHistory = {};
	int i = 0;
	int s;
	while (f >> s){
		if (i%(GRID_WIDTH*GRID_HEIGHT) == 0){ //Ajoute un nouveau tableau à l'historique
			gridHistory.push_back({});
		} 
		if (i%GRID_WIDTH == 0){ //Ajoute une ligne au tableau
			gridHistory[i/(GRID_WIDTH*GRID_HEIGHT)].push_back({});
		}
		gridHistory[i/(GRID_WIDTH*GRID_HEIGHT)][(i/GRID_WIDTH)%GRID_WIDTH].push_back(s);
		i++;
		if (( i%(GRID_WIDTH*GRID_HEIGHT) == 0 ) and ( i/(GRID_WIDTH*GRID_HEIGHT) >= 1 )){
			f >> s;
			gridHistory[i/(GRID_WIDTH*GRID_HEIGHT)-1].push_back({s});
		}
	}
	reset_rand(seed, gridHistory.size());

	return gridHistory;
}
