#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>

#include "common.h"
#include "model.h"
#include "ncurses_cli.h"
#include "save.h"

using namespace std;
/*
int main(){
	vector<matrix> gridHistory = loadFile();
	matrix grid = gridHistory[ gridHistory.size()-1 ];
	dessine(grid);
}
*/

int main(){
	//Initialise le jeu
	start:
	int seed = chrono::steady_clock::now().time_since_epoch().count() * 1000;
	srand(seed);
	matrix grid = plateauInitial();
	reset_rand(seed, 0);
	startScreen();

	//Commence la boucle du jeu
	vector<matrix> gridHistory = {};
	bool alreadyWon = false;
	int move = 0;
	do{
		//Ajoute le plateau à l'historique
		gridHistory.push_back(grid);

		//Affiche le plateau
		int sc = score(grid);
		draw(grid, sc);

		//Affiche le message de victoire
		if (estGagnant(grid)){
			alreadyWon = true;
		}
		if (alreadyWon){
			drawWin();
		}

		//Effectue une action
		matrix newGrid;
		while (true){
			//Demande a l'utilisateur de choisir une action à effectuer
			while (true){
				try{
					move = getUserInput();
					break;
				} catch( invalid_argument &e ){
					invalidMove();
				}
			}
			//Recommence une partie
			if (move == RESTART){ 
				endScreen();
				goto start; }

			//Quitte le programme
			if (move == EXIT){
				endScreen();
				return 0;
			}

			if (move == SAVE){
				saveFile(seed, gridHistory);
				continue;
			}

			if (move == LOAD){
				try{
					gridHistory = loadFile();
					grid = gridHistory[ gridHistory.size()-1 ];
					break;
				} catch (ios_base::failure &e){
					cannotLoad();
					continue;
				}
			}

			//Reviens d'un mouvement en arriere
			if (move == UNDO){
				if (gridHistory.size() > 1){
					grid = gridHistory[gridHistory.size()-2];
					gridHistory.pop_back();
					gridHistory.pop_back();
					int iter = gridHistory.size();
					reset_rand(seed, iter);
					break;
				} else {
					invalidMove();
					continue;
				}
			}
			//Effectue un deplacement
			newGrid = deplacement(grid, move);
			if (grid == newGrid){
				cannotMove();
			} else {
				grid = newGrid;
				break;
			}
		}
	} while (not (estTermine(grid)));

	//Termine le programme en cas de defaite
	int sc = score(grid);
	draw(grid, sc);
	if (drawEnd()){
		endScreen();
		goto start;
	}
	endScreen();
	return 0;
}
