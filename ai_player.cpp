#include <vector>
#include <math.h>

#include "common.h"
#include "model.h"

using namespace std;


int eval_func(matrix grid, int move){
	grid = deplacement(grid, move);
	int initScore = score(grid);

	int delta = 0;
	for (int y = 0; y < GRID_HEIGHT; y++){ for (int x = 0; x < GRID_WIDTH; x++){
		if (y == 0 and x == 0){
			delta += abs( static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y+1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        )
		}
		else if (y == GRID_HEIGHT-1 and x == 0){
			delta += abs( static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        )
		}
		else if (y == 0 and x == GRID_WIDTH-1){
			delta += abs( static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y+1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x-1]))
				        )
		}
		else if (y == GRID_HEIGHT-1 and x == GRID_WIDTH-1){
			delta += abs( static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x-1]))
				        )
		}
		else if (y == 0){
			delta += abs( static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[ y ][x-1]))
				         -static_cast<int>(log2(grid[y+1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        )
		}
		else if (y == GRID_HEIGHT-1){
			delta += abs( static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[ y ][x-1]))
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        )
		}
		else if (x == 0){
			delta += abs( static_cast<int>(log2(grid[ y ][ x ]))
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				         -static_cast<int>(log2(grid[y+1][ x ]))
				        )
		}
		else if (x == GRID_WIDTH-1){
			delta += abs( static_cast<int>(log2(grid[ y ][ x ]))
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x-1]))
				         -static_cast<int>(log2(grid[y+1][ x ]))
				        )
		}
		else {
			delta += abs( static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x-1]))
				         -static_cast<int>(log2(grid[y+1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        )
		}
	}}
	int weight = 10;
	finalScore = initScore - wheight*delta;

	return finalScore;
}


int ai_main(matrix grid){
	int bestMove;
	int bestScore = 0;
	for (int move: {HAUT, BAS, DROITE, GAUCHE}){
		int finalScore = eval_func(grid, move);
		if (finalScore > bestScore){
			bestScore = finalScore;
			bestMove = move;
		}
	}
	return bestMove;
}