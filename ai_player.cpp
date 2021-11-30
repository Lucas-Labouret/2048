#include <vector>
#include <math.h>

#include "common.h"
#include "model.h"

using namespace std;


int eval_func(matrix grid, int move){
	grid = deplacement(grid, move);
	int initScore = grid[GRID_HEIGHT][0];

	int gapPenalty = 0;
	int zeroBonus  = 0;
	for (int y = 0; y < GRID_HEIGHT; y++){ for (int x = 0; x < GRID_WIDTH; x++){
		if (grid[y][x] != 0 and y == 0 and x == 0){
			gapPenalty += abs(
						  static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y+1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        );
		}
		else if (grid[y][x] != 0 and y == GRID_HEIGHT-1 and x == 0){
			gapPenalty += abs(
						  static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        );
		}
		else if (grid[y][x] != 0 and y == 0 and x == GRID_WIDTH-1){
			gapPenalty += abs(
						  static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y+1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x-1]))
				        );
		}
		else if (grid[y][x] != 0 and y == GRID_HEIGHT-1 and x == GRID_WIDTH-1){
			gapPenalty += abs(
						  static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x-1]))
				        );
		}
		else if (grid[y][x] != 0 and y == 0){
			gapPenalty += abs(
						  static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[ y ][x-1]))
				         -static_cast<int>(log2(grid[y+1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        );
		}
		else if (grid[y][x] != 0 and y == GRID_HEIGHT-1){
			gapPenalty += abs(
						  static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[ y ][x-1]))
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        );
		}
		else if (grid[y][x] != 0 and x == 0){
			gapPenalty += abs(
						  static_cast<int>(log2(grid[ y ][ x ]))
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				         -static_cast<int>(log2(grid[y+1][ x ]))
				        );
		}
		else if (grid[y][x] != 0 and x == GRID_WIDTH-1){
			gapPenalty += abs(
						  static_cast<int>(log2(grid[ y ][ x ]))
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x-1]))
				         -static_cast<int>(log2(grid[y+1][ x ]))
				        );
		}
		else if (grid[y][x] != 0) {
			gapPenalty += abs(
						  static_cast<int>(log2(grid[ y ][ x ])) 
				         -static_cast<int>(log2(grid[y-1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x-1]))
				         -static_cast<int>(log2(grid[y+1][ x ]))
				         -static_cast<int>(log2(grid[ y ][x+1]))
				        );
		}
		if (grid[y][x] == 0) {
			zeroBonus += 100;
		}
	}}
	int gapWeight  = initScore;
	int zeroWeight = initScore;
	int finalScore = initScore - gapWeight*gapPenalty + zeroWeight*zeroBonus;

	return finalScore;
}


int aiMain(matrix grid){
	int bestMove;
	int bestScore = -2147483647;
	for (int move: getPossibleMoves(grid)){
		int finalScore = eval_func(grid, move);
		if (finalScore > bestScore){
			bestScore = finalScore;
			bestMove = move;
		}
	}
	return bestMove;;
}