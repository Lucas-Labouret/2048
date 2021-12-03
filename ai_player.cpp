#include <vector>
#include <math.h>

#include "common.h"
#include "model.h"

using namespace std;


int eval_func(matrix grid, int move, int gmovWeight,
									 int gapWeight,
									 int zeroWeight,
									 int scoreWeight){
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
			zeroBonus += 1;
		}
	}}
	int gmovPenalty = 0;
	if (estTermine(grid)){
		gmovPenalty = 1;
	}

	int  finalScore = scoreWeight*initScore
	    			  -gapWeight*gapPenalty
	    			  +zeroWeight*zeroBonus
	    			  -gmovPenalty*gmovWeight;
	return finalScore;
}


int recursiveEval(matrix grid, int iter, int maxIter, int gmovWeight,
									 				  int gapWeight,
									 				  int zeroWeight,
									 				  int scoreWeight){
	int recursiveScore = 0;
	matrix newGrid;
	for (int move: getPossibleMoves(grid)){
		newGrid = deplacement(grid, move);
		if (iter < maxIter ){
			recursiveScore += recursiveEval(newGrid, iter+1, maxIter, gmovWeight, gapWeight, zeroWeight, scoreWeight);
		} else {
			recursiveScore += eval_func(newGrid, move, gmovWeight, gapWeight, zeroWeight, scoreWeight);
		}
	}
	return recursiveScore/4;
}


int aiMain(matrix grid){
	int maxIter     = 4;
	int gmovWeight  = 10;
	int gapWeight   = 10;
	int zeroWeight  = 10;
	int scoreWeight = 1;

	matrix newGrid;
	int bestMove;
	int bestScore = -2147483647;
	for (int move: getPossibleMoves(grid)){
		newGrid = deplacement(grid, move);
		int finalScore = recursiveEval(newGrid, move, maxIter, gmovWeight, gapWeight, zeroWeight, scoreWeight);
		if (finalScore > bestScore){
			bestScore = finalScore;
			bestMove = move;
		}
	}
	return bestMove;
}

int aiMain(matrix grid, vector<int> aiParam){
	int maxIter     = 4;
	int gmovWeight  = aiParam[0];
	int gapWeight   = aiParam[1];
	int zeroWeight  = aiParam[2];
	int scoreWeight = aiParam[3];

	matrix newGrid;
	int bestMove;
	int bestScore = -2147483647;
	for (int move: getPossibleMoves(grid)){
		newGrid = deplacement(grid, move);
		int finalScore = recursiveEval(newGrid, move, maxIter, gmovWeight, gapWeight, zeroWeight, scoreWeight);
		if (finalScore > bestScore){
			bestScore = finalScore;
			bestMove = move;
		}
	}
	return bestMove;
}
