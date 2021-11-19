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
	if (f >> height >> width){
		if (not (height == GRID_HEIGHT and width == GRID_WIDTH)){
			throw ios_base::failure("Saved dimension doesn't match actual dimension");
		}

		int seed;
		f >> seed;

		vector<matrix> gridHistory = {};
		int i = 0;
		int s;
		while (f >> s){
			if (i%16 == 0){ gridHistory.push_back({}); cout << endl; } //Ajoute un nouveau tableau à l'historique
			if (i%4  == 0){ gridHistory[i/16].push_back({}); cout << endl; } //Ajoute une ligne au tableau
			cout << s << " ";
			gridHistory[i/16][(i/4)%4].push_back(s);
		i++;
		}
		reset_rand(seed, gridHistory.size());

		return gridHistory;
	} else {
		throw ios_base::failure("File connot be read");
	}
}
