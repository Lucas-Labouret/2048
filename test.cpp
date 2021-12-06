#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

#define CHECK(test) if (!(test)) cout << "Test failed at line " << __LINE__ << ": " #test << endl


//Test common.cpp
#include "common.h"

int GRID_HEIGHT = 4;
int GRID_WIDTH  = 4;


void commonTest(){
	CHECK(       string("a")*3  == string("aaa")                                 );
	CHECK( string("Pierre ")*5  == string("Pierre Pierre Pierre Pierre Pierre ") );
	CHECK(  string("Pierre")*0  == string("")                                    );
	CHECK(        string("")*12 == string("")                                    );
}


//Test model.cpp
#include "model.h"


void plateauVideTest(){
	matrix emptyGrid = { {0,0,0,0},
						 {0,0,0,0},
						 {0,0,0,0},
						 {0,0,0,0},
						 {0}       };
	CHECK( plateauVide() == emptyGrid );
}


void getValidPositionTest(){
	matrix grid, result;
	grid = { {1,1,1,1},
			 {1,1,1,1},
			 {1,1,1,1},
			 {1,1,1,1},
			 {0}       };
	result = {};
	CHECK(getValidPosition(grid) == result);
	grid = { {0,0,0,0},
			 {0,0,0,0},
			 {0,0,0,0},
			 {0,0,0,0},
			 {0}       };
	result = { {0,0},{0,1},{0,2},{0,3},
		       {1,0},{1,1},{1,2},{1,3},
		       {2,0},{2,1},{2,2},{2,3},
		       {3,0},{3,1},{3,2},{3,3} };
	CHECK( getValidPosition(grid) == result );
	grid = { {1,1,0,0},
			 {0,0,1,1},
			 {0,1,0,0},
			 {0,0,0,1},
			 {4}        };
	result = {             {0,2},{0,3},
		      {1,0},{1,1},
		      {2,0},      {2,2},{2,3},
		            {3,0},{3,1},{3,2} };
	CHECK( getValidPosition(grid) == result );
}


void tireDeuxOuQuatreTest(){
	int counter = 0;
	for (int i = 0; i<10000; i++){
		int test = tireDeuxOuQuatre();
		CHECK( (test == 2)  or (test == 4) );
		if (test == 4) { counter++; }
	}
	CHECK( (0.09 < counter/10000.0) and (counter/10000.0 < 0.11) );
}


void addTwoOrFourTest(){
	matrix grid = { {1,1,1,0},
	                {1,0,1,1},
	                {1,1,1,1},
	                {1,1,1,1},
	                {0}       };
	matrix grid1, grid2, grid3, grid4;
	grid1 = { {1,1,1,2},
              {1,0,1,1},
              {1,1,1,1},
              {1,1,1,1},
              {0}       };
    grid2 = { {1,1,1,4},
              {1,0,1,1},
              {1,1,1,1},
              {1,1,1,1},
              {0}       };
    grid3 = { {1,1,1,0},
              {1,2,1,1},
              {1,1,1,1},
              {1,1,1,1},
              {0}       };
    grid4 = { {1,1,1,0},
              {1,4,1,1},
              {1,1,1,1},
              {1,1,1,1},
              {0}       };
	for (int i = 0; i < 10000; i++){
		  matrix newGrid = addTwoOrFour(grid);
		  CHECK(     (newGrid == grid1) 
			      or (newGrid == grid2)
			      or (newGrid == grid3)
			      or (newGrid == grid4)
		       );
	}
}


void checkMoveTest(){
	matrix gridH, gridB, gridG, gridD, gridN, gridT;
	gridH = { {0,2,2,0},
			  {0,0,0,0},
			  {0,0,0,0},
			  {0,0,0,0},
			  {0}       };
	gridB = { {0,0,0,0},
			  {0,0,0,0},
			  {0,0,0,0},
			  {2,2,2,2},
			  {0}       };
	gridG = { {2,0,0,0},
			  {2,0,0,0},
			  {2,0,0,0},
			  {2,0,0,0},
			  {0}       };
	gridD = { {4,2,4,2},
			  {0,8,4,2},
			  {8,16,4,2},
			  {4,2,4,2},
			  {0}       };
	gridN = { {0,0,0,0},
			  {0,2,4,0},
			  {0,4,2,0},
			  {0,0,0,0},
			  {0}       };
	gridT = { {2,4,8,16},
			  {32,64,128,256},
			  {512,1024,2048,4096},
			  {8192,16384,32768,65536},
			  {0}                      };

	CHECK( not checkMove(gridH, HAUT  ) );
	CHECK(     checkMove(gridH, BAS   ) );
	CHECK(     checkMove(gridH, DROITE) );
	CHECK(     checkMove(gridH, GAUCHE) );

	CHECK(     checkMove(gridB, HAUT  ) );
	CHECK( not checkMove(gridB, BAS   ) );
	CHECK(     checkMove(gridB, DROITE) );
	CHECK(     checkMove(gridB, GAUCHE) );

	CHECK(     checkMove(gridD, HAUT  ) );
	CHECK(     checkMove(gridD, BAS   ) );
	CHECK( not checkMove(gridD, DROITE) );
	CHECK(     checkMove(gridD, GAUCHE) );

	CHECK(     checkMove(gridG, HAUT  ) );
	CHECK(     checkMove(gridG, BAS   ) );
	CHECK(     checkMove(gridG, DROITE) );
	CHECK( not checkMove(gridG, GAUCHE) );

	CHECK(     checkMove(gridN, HAUT  ) );
	CHECK(     checkMove(gridN, BAS   ) );
	CHECK(     checkMove(gridN, DROITE) );
	CHECK(     checkMove(gridN, GAUCHE) );

	CHECK( not checkMove(gridT, HAUT  ) );
	CHECK( not checkMove(gridT, BAS   ) );
	CHECK( not checkMove(gridT, DROITE) );
	CHECK( not checkMove(gridT, GAUCHE) );

}


void deplacementHautTest(){
	matrix start, result;

	start  = {{0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	CHECK( deplacementHaut(start) == result );

	start  = {{0,4,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,4,0,0},
	          {0,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	CHECK( deplacementHaut(start) == result );

	start  = {{0,2,0,0},
	          {0,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,4,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementHaut(start) == result );

	start  = {{0,0,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,4,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementHaut(start) == result );

	start  = {{0,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,4,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementHaut(start) == result );

	start  = {{0,2,0,0},
	          {0,4,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,2,0,0},
	          {0,4,0,0},
	          {0,2,0,0},
	          {0,0,0,0},
	          {0}      };
	CHECK( deplacementHaut(start) == result );

	start  = {{0,2,0,0},
	          {0,2,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,4,0,0},
	          {0,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementHaut(start) == result );

	start  = {{0,2,0,0},
	          {0,2,0,0},
	          {0,2,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,4,0,0},
	          {0,4,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {8}      };
	CHECK( deplacementHaut(start) == result );
}


void deplacementBasTest(){
	matrix start, result;

	start  = {{0,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0}      };
	CHECK( deplacementBas(start) == result );

	start  = {{0,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,4,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0,4,0,0},
	          {0}      };
	CHECK( deplacementBas(start) == result );

	start  = {{0,0,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,4,0,0},
	          {4}      };
	CHECK( deplacementBas(start) == result );

	start  = {{0,2,0,0},
	          {0,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,4,0,0},
	          {4}      };
	CHECK( deplacementBas(start) == result );

	start  = {{0,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0,4,0,0},
	          {4}      };
	CHECK( deplacementBas(start) == result );

	start  = {{0,2,0,0},
	          {0,0,0,0},
	          {0,4,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,2,0,0},
	          {0,4,0,0},
	          {0,2,0,0},
	          {0}      };
	CHECK( deplacementBas(start) == result );

	start  = {{0,2,0,0},
	          {0,2,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,0},
	          {0,2,0,0},
	          {0,4,0,0},
	          {4}      };
	CHECK( deplacementBas(start) == result );

	start  = {{0,2,0,0},
	          {0,2,0,0},
	          {0,2,0,0},
	          {0,2,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,0},
	          {0,4,0,0},
	          {0,4,0,0},
	          {8}      };
	CHECK( deplacementBas(start) == result );
}


void deplacementDroiteTest(){
	matrix start, result;

	start  = {{0,0,0,0},
	          {2,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	CHECK( deplacementDroite(start) == result );

	start  = {{0,0,0,0},
	          {2,0,0,4},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,2,4},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	CHECK( deplacementDroite(start) == result );

	start  = {{0,0,0,0},
	          {0,0,2,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,4},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementDroite(start) == result );

	start  = {{0,0,0,0},
	          {2,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,4},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementDroite(start) == result );

	start  = {{0,0,0,0},
	          {2,0,0,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,0,4},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementDroite(start) == result );

	start  = {{0,0,0,0},
	          {2,4,0,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,2,4,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	CHECK( deplacementDroite(start) == result );

	start  = {{0,0,0,0},
	          {2,2,0,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,2,4},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementDroite(start) == result );

	start  = {{0,0,0,0},
	          {2,2,2,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {0,0,4,4},
	          {0,0,0,0},
	          {0,0,0,0},
	          {8}      };
	CHECK( deplacementDroite(start) == result );
}


void deplacementGaucheTest(){
	matrix start, result;

	start  = {{0,0,0,0},
	          {0,0,0,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {2,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	CHECK( deplacementGauche(start) == result );

	start  = {{0,0,0,0},
	          {4,0,0,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {4,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	CHECK( deplacementGauche(start) == result );

	start  = {{0,0,0,0},
	          {2,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {4,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementGauche(start) == result );

	start  = {{0,0,0,0},
	          {0,0,2,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {4,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementGauche(start) == result );

	start  = {{0,0,0,0},
	          {2,0,0,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {4,0,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementGauche(start) == result );

	start  = {{0,0,0,0},
	          {2,4,0,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {2,4,2,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	CHECK( deplacementGauche(start) == result );

	start  = {{0,0,0,0},
	          {2,0,2,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {4,2,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {4}      };
	CHECK( deplacementGauche(start) == result );

	start  = {{0,0,0,0},
	          {2,2,2,2},
	          {0,0,0,0},
	          {0,0,0,0},
	          {0}      };
	result = {{0,0,0,0},
	          {4,4,0,0},
	          {0,0,0,0},
	          {0,0,0,0},
	          {8}      };
	CHECK( deplacementGauche(start) == result );
}


void estTermineTest(){
	matrix grid;
	grid = {{0,0,0,0},
	        {4,4,0,0},
	        {0,0,0,0},
	        {0,0,0,0},
	        {8}      };
	CHECK( not estTermine(grid) );

	grid = {{4,4,4,4},
	        {4,4,4,4},
	        {4,4,4,4},
	        {4,4,4,4},
	        {8}      };
	CHECK( not estTermine(grid) );

	grid = {{2,4,2,4},
	        {4,2,4,2},
	        {2,4,2,4},
	        {4,2,4,2},
	        {4}      };
	CHECK( estTermine(grid) );
}


void estGagnantTest(){
	matrix grid;
	grid = {{0,0,0,0},
	        {4,4,0,0},
	        {0,0,0,0},
	        {0,0,0,0},
	        {8}      };
	CHECK( not estGagnant(grid) );

	grid = {{0,0,0   ,0},
	        {4,4,0   ,0},
	        {0,0,2048,0},
	        {0,0,0   ,0},
	        {8}         };
	CHECK( estGagnant(grid) );

	grid = {{0,0,0   ,0},
	        {4,4,0   ,0},
	        {0,0,4096,0},
	        {0,0,0   ,0},
	        {8}         };
	CHECK( estGagnant(grid) );

	grid = {{0,0,2048,0},
	        {4,4,0   ,0},
	        {0,0,4096,0},
	        {0,0,0   ,0},
	        {8}         };
	CHECK( estGagnant(grid) );

	grid = {{0,0,0,0},
	        {4,4,0,0},
	        {0,0,0,0},
	        {0,0,0,0},
	        {2048}   };
	CHECK( not estGagnant(grid) );
}


void modelTest(){
	//Test plateauVide()
	plateauVideTest();

	//Test getValidPosition()
	getValidPositionTest();
	
	//Test tireDeuxOuQuatre()
	tireDeuxOuQuatreTest();

	//Test addTwoOrFour()
	addTwoOrFourTest();

	//Test checkMove()
	checkMoveTest();

	//Test deplacementHaut()
	deplacementHautTest();

	//Test deplacementBas()
	deplacementBasTest();

	//Test deplacementDroite()
	deplacementDroiteTest();

	//Test deplacementGauche()
	deplacementGaucheTest();

	//Test estTermine()
	estTermineTest();

	//Test estGagant()
	estGagnantTest();
}


int main(){
	srand(0);

	commonTest();
	modelTest();

	return 0;
}
