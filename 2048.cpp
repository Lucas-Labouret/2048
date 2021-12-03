#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <algorithm>

#include "common.h"
#include "model.h"
#include "ncurses_cli.h"
#include "save.h"
#include "ai_player.h"

using namespace std;

vector<string> VALID_ARGUMENT = {"--height", "--width", "--AI"};
int GRID_HEIGHT = 4;
int GRID_WIDTH = 4;
int PLAYER = HUMAN;


bool mainLoop(){
	/**Gère le déroulement d'une partie
	 * @return true si le joueur souhaite recommencer une partie, false sinon
	**/
	//Initialise le jeu
	int seed = chrono::steady_clock::now().time_since_epoch().count() * 1000;
	srand(seed);
	matrix grid = plateauInitial();/*{{0,0,0,0},{0,0,0,0},{0,1024,1024,0},{0,0,0,0}};*/
	reset_rand(seed, 0);

	//Commence la boucle du jeu
	vector<matrix> gridHistory = {};
	bool alreadyWon = false;
	int move = 0;
	do{
		//Ajoute le plateau à l'historique
		gridHistory.push_back(grid);

		//Affiche le plateau
		draw(grid);

		//Affiche le message de victoire
		if (estGagnant(grid)){
			drawWin();
		}

		//Effectue une action
		matrix newGrid;
		while (true){
			//Demande au joueur de choisir une action à effectuer
			if (PLAYER == HUMAN){ //Si le joueur est humain 
				while (true){
					try{
						move = getUserInput();
						break;
					} catch( invalid_argument &e ){
						invalidMove();
					}
				}
			} else { //Si le joueur est une IA
				move = aiMain(grid);
			}
			//Recommence une partie
			if (move == RESTART){ 
				return true; }

			//Quitte le programme
			if (move == EXIT){
				return false;
			}

			if (move == SAVE){
				saveFile(seed, gridHistory);
				drawSave();
				continue;
			}

			if (move == LOAD){
				try{
					gridHistory = loadFile();
					grid = gridHistory[ gridHistory.size()-1 ];
					gridHistory.pop_back();
					break;
				} catch (ios_base::failure &e){
					cannotLoad(e.what());
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
				continue;
			} else {
				grid = newGrid;
				break;
			}
		}
	} while (not (estTermine(grid)));

	//Termine la partie en cas de defaite
	draw(grid);
	/*
	if (PLAYER == AI){
		saveScore(grid[GRID_HEIGHT][0]);
	}
	*/
	return drawEnd(); //Permet au joueur de choisir s'il veut quitter le jeu ou recommencer une partie
}


void parseCmd(int argc, char *argv[]){
	/**Parse les arguments passés dnas le terminal
	 * @param argc le nombre d'argument passé
	 * @param *argv[] un tableau de chaines de caractère représentant les argument
	**/
	for (int i = 1; i < argc; i++){
		if (not count(VALID_ARGUMENT.begin(), VALID_ARGUMENT.end(), string(argv[i]))){
			throw invalid_argument(string(argv[i]) + " is not a valid argument.");
		}
		if (string(argv[i]) == "--height"){ //
			if (i+1 >= argc){
				throw out_of_range("\"--height\" doit être suivie d'un entier supérieur ou égal à 2.");
			}
			GRID_HEIGHT = atoi(argv[++i]);
			if (GRID_HEIGHT < 2){
				throw invalid_argument("\"--height\" doit être suivie d'un entier supérieur ou égal à 2.");
			}
		}
		if (string(argv[i]) == "--width"){
			if (i+1 >= argc){
				throw out_of_range("\"--width\" doit être suivie d'un entier supérieur ou égal à 2.");
			}
			GRID_WIDTH = atoi(argv[++i]);
			if (GRID_WIDTH < 2){
				throw invalid_argument("\"--width\" doit être suivie d'un entier supérieur ou égal à 2.");
			}
		}
		if (string(argv[i]) == "--AI"){
			PLAYER = AI;
		}
	}
}


int main(int argc, char *argv[]){
	//Parse les arguments passés dnas le terminal
	if (argc > 1){
		try{
			parseCmd(argc, argv);
		} catch (out_of_range &e){
			cerr << e.what() << endl;
			return 0;
		} catch (invalid_argument &e){
			cerr << e.what() << endl;
			return 0;
		}
	}

	//Lance une partie et en recommence d'autres tant que le joueur le demande
	startScreen();
	while (mainLoop());
	endScreen();
	return 0;
}
