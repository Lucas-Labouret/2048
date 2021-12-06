#include <vector>
#include <fstream>
#include <iostream>

#include "common.h"
#include "model.h"
#include "ai_player.h"

using namespace std;

int GRID_HEIGHT = 4;
int GRID_WIDTH  = 4;

int GEN_SIZE = 100;
int MAX_GEN  = 60;
int AVG_SIZE = 50;

typedef vector<vector<int>> generation;
typedef vector<int> indiv;

int mainLoop(indiv aiParam){
	/**Fait jouer une partie à une IA
	 * @param aiParam les paramètres de l'IA
	 * @return le score à la fin de la partie
	**/
	//Initialise le jeu
	matrix grid = plateauInitial();

	//Commence la boucle du jeu
	int move = 0;
	do{
		//Demande à l'IA de choisir le déplacement à effectuer
		move = aiMain(grid, aiParam);

		//Effectue un deplacement
		grid = deplacement(grid, move);

	} while (not (estTermine(grid)));
	
	//Renvoie le score à la fin de la partie
	return grid[GRID_HEIGHT][0];
}


generation newGen(indiv Adam, int genIndex){
	generation gen = generation(GEN_SIZE);
	gen[0] = Adam;
	for (int i = 1; i < GEN_SIZE; i++){
		indiv someGuy = indiv(Adam.size());
		for (int n = 0; n < Adam.size(); n++){
			someGuy[n] = Adam[n] + (1000*((rand()%20)-10))/(genIndex+1); 
		}
		gen[i] = someGuy;
	}
	return gen;
}


void toFile(vector<generation> genHistory, vector<vector<int>> scoreHistory, indiv bestGuy, int bestScore){
	ofstream f("training_result.txt");
	f << "GRID_HEIGHT = " << GRID_HEIGHT << endl;
	f << "GRID_WIDTH  = " << GRID_WIDTH  << endl;
	f << "GEN_SIZE    = " << GEN_SIZE    << endl;
	f << "MAX_GEN     = " << MAX_GEN     << endl;
	f << "AVG_SIZE    = " << AVG_SIZE    << endl;
	f << endl;

	f << "Best AI:   " << endl;
	f << "gmovWeight  = " << bestGuy[0] << endl;
	f << "gapWeight   = " << bestGuy[1] << endl;
	f << "zeroWeight  = " << bestGuy[2] << endl;
	f << "scoreWeight = " << bestGuy[3] << endl;
	f << "posWeight   = " << bestGuy[4] << endl;
	f << "Score: " << bestScore << endl;
	f << endl;

	for (int genIndex = 0; genIndex < MAX_GEN; genIndex++){
		f << "generation " << genIndex+1 << endl;
		for (int indivIndex = 0; indivIndex < GEN_SIZE; indivIndex++){
			f << indivIndex << ": ";
			for (int v: genHistory[genIndex][indivIndex]){
				f << v << " ";
			}
			f << "| " << scoreHistory[genIndex][indivIndex] << endl;
		}
		f << endl;
	}
	f.close();

}


int main(){
	srand(0);
	indiv bestGuy = {10000, 10000, 10000, 10000, 10000};
	int bestScore;
	vector<generation> genHistory = {};
	vector<vector<int>> scoreHistory = {};
	for (int genIndex = 0; genIndex < MAX_GEN; genIndex++){
		cout << "gen " << genIndex+1 << ": ";
		cout.flush();
		generation gen = newGen(bestGuy, genIndex);
		genHistory.push_back(gen);
		scoreHistory.push_back({});
		for (indiv someGuy: gen){
			int total = 0;
			for (int _ = 0; _ < AVG_SIZE; _++){
				total += mainLoop(someGuy);
			}
			int score = total/AVG_SIZE;
			if (score > bestScore){
				bestScore = score;
				bestGuy  = someGuy;
			}
			scoreHistory[genIndex].push_back(score);
			cout << "-";
			cout.flush();
		}
		cout << endl;
		cout.flush();
	}
	toFile(genHistory, scoreHistory, bestGuy, bestScore);
	cout << "Done" << endl;
	cout.flush();
}
