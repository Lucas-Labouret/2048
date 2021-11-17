#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>

#include "common.h"
#include "model.h"
#include "ncurses_cli.h"

using namespace std;


int main(){
	//Recommence une partie tant que le joueur ne veut pas s'arrèter
	while (true){
		//Initialise le jeu
		float seed = chrono::steady_clock::now().time_since_epoch().count();
		srand(seed);
		matrix grid = plateauInitial();
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
				if (move == RESTART){ break; }

				//Quitte le programme
				if (move == EXIT){
					endScreen();
					return 0;
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
				if (move == RESTART){ break; }
			}
		} while (not (estTermine(grid)));

		if (move == RESTART){ break; }
		//Termine le programme en cas de defaite
		int sc = score(grid);
		draw(grid, sc);
		drawEnd();
		endScreen();
		return 0;
	}
}
