#include <vector>

#include "common.h"
#include "ai_player.h"

using namespace std;

bool mainLoop(vector<int> aiParam){
	/**Fait jouer une partie à une IA
	 * @param aiParam les paramètres de l'IA
	 * @return le score à la fin de la partie
	**/
	//Initialise le jeu
	int seed = chrono::steady_clock::now().time_since_epoch().count() * 1000;
	srand(seed);
	matrix grid = plateauInitial();
	reset_rand(seed, 0);

	//Commence la boucle du jeu
	int move = 0;
	do{
		//Demande à l'IA de choisir le déplacement à effectuer
		move = aiMain(grid, aiParam);

		//Effectue un deplacement
		grid = deplacement(grid, move);

	} while (not (estTermine(grid)));
	
	return grid[GRID_HEIGHT][0];
}
