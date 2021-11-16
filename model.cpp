#include <iostream>
#include <vector>
#include <math.h>

#include "model.h"

using namespace std;


string operator * (string str, unsigned int n){
	/** permet de multiplier des chaines de caractere par des entier positif de la meme facon qu'en python
	 * @param str la chaine de caractere
	 * @param n le nombre de repetition
	 * @return str concataine n-1 fois avec lui-même
	**/
    string output = "";
    while (n--) {
        output += str;
    }
    return output;
}


matrix plateauVide(){
	/** Construit le plateau de jeu 
	 * @return un tableau 2D de dimension GRID_WIDTH*GRID_HEIGHT rempli de zéro
	**/
	matrix grid = matrix(GRID_HEIGHT);
	for (auto &line: grid){
		line = vector<int>(GRID_WIDTH);
		for (auto &cell: line){
			cell = 0;
		}
	}
	return grid;
}


matrix getValidPosition(matrix grid){
	/** Liste les positions où il est possible de rajouter un 2 ou un 4
	 * @param grid le plateau de jeu
	 * @return un tableau de coordonnées de la forme {{y0, x0}, {y1,x1}, ...}
	**/ 
	matrix validPosition = {};
	for (int y = 0; y < grid.size(); y++){
		for (int x = 0; x < grid[y].size(); x++){
			if (grid[y][x] == 0){
				validPosition.push_back({y, x});
			}
		}
	}
	return validPosition;
}


int tireDeuxOuQuatre(){
	/** Tire aleatoirement 2 ou 4 avec une probabilité respctive de 0.9 et 0.1
	 * @return 2 ou 4
	**/
	if (rand()%10 == 0){return 4;}
	return 2;
}


matrix addTwoOrFour(matrix grid){
	/** Ajoute aleatoirement 2 ou 4 dans une case vide
	 * @param grid le plateau de jeu
	 * @return le plateau de jeu modifie
	**/ 
	matrix validPosition = getValidPosition(grid);
	vector<int> position = validPosition[rand() % validPosition.size()];
	int y = position[0];
	int x = position[1];
	grid[y][x] = tireDeuxOuQuatre();
	return grid;
}


matrix plateauInitial(){
	/** Cree le plateau de jeu initial et y ajoute deux tuiles indépendantes de valeur 2 ou 4
	 * @return le plateau initial
	**/
	matrix grid = plateauVide();
	grid = addTwoOrFour(grid);
	grid = addTwoOrFour(grid);
	return grid;
}


bool checkMove(matrix grid, int move){
	/** Verifie qu'un mouvement donne peut-etre effectue. (Il es alors dit "possible")
	 * @param grid le plateau
	 * @param move le mouvement a tester
	 * return true si le mouvement est possible, false sinon
	**/
	switch( move ){
		case HAUT:
			for (int y = 1; y < grid.size(); y++)
				for (int x = 0; x<grid[y].size(); x++)
					if ( ((grid[y-1][x] == 0) or (grid[y-1][x] == grid[y][x])) and grid[y][x] != 0 ){
						return true;
					}
			break;

		case BAS:
			for (int y = 0; y < grid.size()-1; y++)
				for (int x = 0; x<grid[y].size(); x++)
					if ( ((grid[y+1][x] == 0) or (grid[y+1][x] == grid[y][x])) and grid[y][x] != 0 ){
						return true;
					};
			break;

		case GAUCHE:
			for (int y = 0; y < grid.size(); y++)
				for (int x = 1; x<grid[y].size(); x++)
					if ( ((grid[y][x-1] == 0) or (grid[y][x-1] == grid[y][x])) and grid[y][x] != 0 ){
						return true;
					}
			break;

		case DROITE:
			for (int y = 0; y < grid.size(); y++)
				for (int x = 0; x<grid[y].size()-1; x++)
					if ( ((grid[y][x+1] == 0) or (grid[y][x+1] == grid[y][x])) and grid[y][x] != 0 ){
						return true;
					}
			break;

		default:
		    return false;
		    break;
	}
	return false;
}


vector<int> getPossibleMoves(matrix grid){
	/** Verifie que chaque mouvement est possible
	 * @param grid le plateau
	 * @return une liste de mouvement possible
	*/
	vector<int> moves = {HAUT, BAS, GAUCHE, DROITE};
	vector<int> possibleMoves = {};
	for (auto move: moves){
		if (checkMove(grid, move)){
			possibleMoves.push_back(move);
		}
	}
	return possibleMoves;
}


matrix deplacementHaut(matrix grid){
	/** Effectue un deplacement vers le haut
	 * @grid le plateau
	 * @return le nouveau plateau
	**/
	for (int x = 0; x < GRID_WIDTH; x++){
        for (int y = 0; y < GRID_HEIGHT - 1; y++){
            bool valChanged = false;
            for (int sub_y = 1; y+sub_y < GRID_HEIGHT; sub_y++){
                if ((grid[y][x] == 0) and (grid[y+sub_y][x] != 0)){
                    grid[y][x] = grid[y+sub_y][x];
                    grid[y+sub_y][x] = 0;
                }
                bool interValue = false;
                for (int i = 1; i < sub_y; i++){
                    if (grid[y+i][x] != 0){
                        interValue = true;
                    }
                }
                if ((grid[y][x] == grid[y+sub_y][x]) and (not interValue)){
                    if (not valChanged){
                        grid[y][x] *= 2;
                        grid[y+sub_y][x] = 0;
                        valChanged = true;
                    }else if (grid[y+1][x] == 0){
                        grid[y+1][x] = grid[y+sub_y][x];
                        grid[y+sub_y][x] = 0;
                    }
                }
            }
        }
    }
	return grid;
}


matrix deplacementBas(matrix grid){
	/** Effectue un deplacement vers le bas
	 * @grid le plateau
	 * @return le nouveau plateau
	**/
	for (int x = 0; x < GRID_WIDTH; x++){
        for (int y = GRID_HEIGHT-1; y > 0; y--){
            bool valChanged = false;
            for (int sub_y = 1; y-sub_y >= 0; sub_y++){
                if ((grid[y][x] == 0) and (grid[y-sub_y][x] != 0)){
                    grid[y][x] = grid[y-sub_y][x];
                    grid[y-sub_y][x] = 0;
                }
                bool interValue = false;
                for (int i = 1; i < sub_y; i++){
                    if (grid[y-i][x] != 0){
                        interValue = true;
                    }
                }
                if ((grid[y][x] == grid[y-sub_y][x]) and (not interValue)){
                    if (not valChanged){
                        grid[y][x] *= 2;
                        grid[y-sub_y][x] = 0;
                        valChanged = true;
                    }else if (grid[y-1][x] == 0){
                        grid[y-1][x] = grid[y-sub_y][x];
                        grid[y-sub_y][x] = 0;
                    }
                }
            }
        }
    }
	return grid;
}


matrix deplacementGauche(matrix grid){
	/** Effectue un deplacement vers la gauche
	 * @grid le plateau
	 * @return le nouveau plateau
	**/
	for (int y = 0; y < GRID_HEIGHT; y++){
        for (int x = 0; x < GRID_WIDTH - 1; x++){
            bool valChanged = false;
            for (int sub_x = 1; x+sub_x < GRID_WIDTH; sub_x++){
                if ((grid[y][x] == 0) and (grid[y][x+sub_x] != 0)){
                    grid[y][x] = grid[y][x+sub_x];
                    grid[y][x+sub_x] = 0;
                }
                bool interValue = false;
                for (int i = 1; i < sub_x; i++){
                    if (grid[y][x+i] != 0){
                        interValue = true;
                    }
                }
                if ((grid[y][x] == grid[y][x+sub_x]) and (not interValue)){
                    if (not valChanged){
                        grid[y][x] *= 2;
                        grid[y][x+sub_x] = 0;
                        valChanged = true;
                    }else if (grid[y][x+1] == 0){
                        grid[y][x+1] = grid[y][x+sub_x];
                        grid[y][x+sub_x] = 0;
                    }
                }
            }
        }
    }
	return grid;
}


matrix deplacementDroite(matrix grid){
	/** Effectue un deplacement vers la droite
	 * @grid le plateau
	 * @return le nouveau plateau
	**/
	for (int y = 0; y < GRID_HEIGHT; y++){
        for (int x = GRID_WIDTH-1; x > 0; x--){
            bool valChanged = false;
            for (int sub_x = 1; x-sub_x >= 0; sub_x++){
                if ((grid[y][x] == 0) and (grid[y][x-sub_x] != 0)){
                    grid[y][x] = grid[y][x-sub_x];
                    grid[y][x-sub_x] = 0;
                }
                bool interValue = false;
                for (int i = 1; i < sub_x; i++){
                    if (grid[y][x-i] != 0){
                        interValue = true;
                    }
                }
                if ((grid[y][x] == grid[y][x-sub_x]) and (not interValue)){
                    if (not valChanged){
                        grid[y][x] *= 2;
                        grid[y][x-sub_x] = 0;
                        valChanged = true;
                    }else if (grid[y][x-1] == 0){
                        grid[y][x-1] = grid[y][x-sub_x];
                        grid[y][x-sub_x] = 0;
                    }
                }
            }
        }
    }
	return grid;
}


matrix deplacement(matrix grid, int move){
	/** Selectionne le mouvement a effectuer
	 * @param grid le plateau
	 * @param move le mouvement a effectuer
	 * @return le nouveau plateau
	**/
	matrix newGrid;
	switch( move ){
		case HAUT:
			newGrid = deplacementHaut(grid);
			break;
		case BAS:
			newGrid = deplacementBas(grid);
			break;
		case GAUCHE:
			newGrid = deplacementGauche(grid);
			break;
		case DROITE:
			newGrid = deplacementDroite(grid);
			break;
	};
	if (grid == newGrid){
		return grid;
	} else {
		grid = addTwoOrFour(newGrid);
		return grid;
	}
}


bool estTermine(matrix grid){
	/** Verifie si la partie est termine, i.e. si plus aucun mouvement n'est possible
	 * @param grid le plateau
	 * @return true si la partie est terminz, false sinon
	**/
	vector<int> possibleMoves = getPossibleMoves(grid);
	return (possibleMoves.empty());
}


bool estGagnant(matrix grid){
	/** Verifie si la partie a ete gagne, i.e. si une tuile contient 2048 ou plus
	 * @param grid le plateau
	 * @return true si la partie a ete gagne, false sinon
	**/
	for (auto line: grid){
		for (auto cell: line){
			if (cell >= 2048){ return true; }
		}
	}
	return false;
}


int score(matrix grid){
	/** Calcul le score d'un plateau donne
	 * @param grid le plateau
	 * @return le score
	**/
	int s = 0;
	for (auto line: grid){
		for (auto cell: line){
			if (cell!=0){
				s += (static_cast<int>(log2(cell)) - 1) * cell;
			}
		}
	}
	return s;
}


string dessine(matrix grid){
	/** Construit une chaine de caracteres représentant le plateau
	 * @param grid le plateau
	 * @return une chaine de caracteres représentant le plateau
	**/
	vector<vector<string>> strGrid = {};
	int max_len = 0;
	for (auto &line: grid){
		vector<string> strLine = {};
		for (auto &cell: line){
			string strCell = to_string(cell);
			if (strCell.size() > max_len){
				max_len = strCell.size();
			}
			if (strCell == "0"){ strLine.push_back(" "); }
			else { strLine.push_back(strCell); }
		}
		strGrid.push_back(strLine);
	}

	string str2048 = "";
	string star = "*";
	string space = " ";
	string head = "";
	string sc = to_string(score(grid));

	string separator =  (star * (GRID_WIDTH+1)) 
		               +(star * max_len * GRID_WIDTH) 
		               +"\n";

	if (separator.size()%2 == 0){
		head =  "Score: " + sc + "\n"
		       +( star * (separator.size()/2 - 3) ) + "2048"
			   +( star * (separator.size()/2 - 2) ) + "\n";
	} else {
		head =  "Score: " + sc + "\n"
		       +( star * (separator.size()/2 - 2) ) + "2048"
			   +( star * (separator.size()/2 - 2) ) + "\n";
	}

    str2048 += head;
	for (auto line: strGrid){
		for (auto cell: line){
			if ((max_len-cell.size())%2 == 0){
				str2048 +=  star + (space * (((max_len-cell.size()))/2))
						   +cell +(space * (((max_len-cell.size()))/2));
			} else {
				str2048 +=  star + (space * (((max_len-cell.size()))/2))
						   +cell + (space * (((max_len-cell.size()))/2 + 1));
			}
			
		}
		str2048 += star + "\n" + separator;
	}
	return str2048;
}


void reset_rand(float seed, int iter){
	srand(seed);
	rand();
	rand();
	for (int i = 1; i < iter; i++){ rand(); }
}
