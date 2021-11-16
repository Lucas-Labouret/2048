#include <iostream>
#include <vector>
#include <ncurses.h>
#include <math.h>
#include <algorithm>
#include <stdexcept>

#include "common.h"
#include "ncurses_cli.h"

using namespace std;


void startScreen(){
	/**Configure la fenetre ncurses
	**/
	initscr();
	keypad(stdscr, true);
	curs_set(0);
	start_color();
}


void endScreen(){
	/**Ferme la fenetre ncurses
	**/
	endwin();
}


int mapMove(int input){
	/**Associe a chaque deplacement un entier
	 * @param input l'ID de la touche pressee par l'utilisateur
	 * @return l'entier associé au deplacement
	**/
	if (count(VALID_KEYS.begin(), VALID_KEYS.end(), input) == 0){
		throw invalid_argument("invalid key");
	}
	int move;
	if (input == VALID_KEYS[0]){
		move = HAUT;
	}
	if (input == VALID_KEYS[1]){
		move = GAUCHE;
	}
	if (input == VALID_KEYS[2]){
		move = BAS;
	}
	if (input == VALID_KEYS[3]){
		move = DROITE;
	}
	if (input == VALID_KEYS[4]){
		move = UNDO;
	}
	if (input == VALID_KEYS[5]){
		move = EXIT;
	}
	return move;
}


int getUserInput(){
	/**Demande a l'utilisateur de saisir une action a effectuer
	**/
	int input = getch();
	return mapMove(input);
}


void draw(matrix grid, int sc){
	/**Affiche le jeu dans la console
	 * @param grid le plateau
	 * @param sc le score actuel
	**/
	//Construit un tableau 2D de chaine de caractères correspondant au plateau
	//Determine la longeur de la tuile la plus longue
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

	//Déclare les pairs de couleurs utiliser pour afficher le jeu
	init_pair(1, COLOR_CYAN   , COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW , COLOR_BLACK);

	//Déclare les caractère utiliser pour afficher la grille
	string star = "*";
	string space = " ";
	
	//Efface tout ce qu'il y a l'ecran
	clear();

	//Affiche le score
	move(Y_MARGIN ,X_MARGIN);
	attron(COLOR_PAIR(1));
	printw("Score: ");
	attroff(COLOR_PAIR(1)); attron(COLOR_PAIR(2));
	printw(to_string(sc).c_str());
	attroff(COLOR_PAIR(2));

	//Construit la chaine de caracteres utilisee pour separer chaque ligne du plateau
	string separator =  (star * (GRID_WIDTH+1)) 
		               +(star * max_len * GRID_WIDTH);

	//Affiche la tete du plateau
	attron(COLOR_PAIR(1));
	if (separator.size()%2 == 0){
		mvprintw(Y_MARGIN+1, X_MARGIN, ( star * (separator.size()/2 - 2) ).c_str());
	} else {
		mvprintw(Y_MARGIN+1, X_MARGIN, ( star * (separator.size()/2 - 1) ).c_str());
	}
	attroff(COLOR_PAIR(1)); attron(COLOR_PAIR(2));
	printw("2048");
	attroff(COLOR_PAIR(2)); attron(COLOR_PAIR(1));
	printw( (star * (separator.size()/2 - 2)).c_str() );
	attroff(COLOR_PAIR(1));

	//Affiche le plateau de jeu
	for (int y = 0; y < GRID_HEIGHT; y++){ //Affiche chaque ligne du plateau
		move(Y_MARGIN+2+2*y, X_MARGIN);
		for (int x = 0; x < GRID_WIDTH; x++){ //Affiche chaque tuile d'une ligne

			//Centre la tuile dans une case
			string cell = strGrid[y][x];
			attron(COLOR_PAIR(1));
			printw((star + (space * ((max_len-cell.size())/2))).c_str());
			attroff(COLOR_PAIR(1));

			//Affiche la tuile
			int delta = 0;
			int logCell = 0;
			if (grid[y][x] != 0){
				//Rend plus rouge les tuile plus grande
				logCell = static_cast<int>(log2(grid[y][x])-1);
				delta = 50*logCell;
				init_color(10+logCell, 1000, max(0,1000-delta), max(0,1000-delta));
				init_pair(10+logCell, 10+logCell, COLOR_BLACK);
				attron(COLOR_PAIR(10+logCell));
				printw(cell.c_str());
				attron(COLOR_PAIR(10+logCell));
			} else {
				printw(cell.c_str());
			}

			//Centre la tuile dans une case
			if ((max_len-cell.size())%2 == 0){
				printw((space * (((max_len-cell.size()))/2)).c_str());
			} else {
				printw((space * ((max_len-cell.size())/2 + 1)).c_str());
			}
			
		}
		//Complète la ligne et affiche une ligne de séparation avant la suivante
		attron(COLOR_PAIR(1));
		printw(star.c_str());
		move(Y_MARGIN+3+2*y, X_MARGIN);
		printw(separator.c_str());
		attroff(COLOR_PAIR(1));
	}
	//Affiche les instructions
	attron(COLOR_PAIR(3));
	mvprintw(2*GRID_HEIGHT+Y_MARGIN+7,  X_MARGIN, "|--------------------------Instructions---------------------------|");
	mvprintw(2*GRID_HEIGHT+Y_MARGIN+8,  X_MARGIN, "|             Jouez avec les flèches directionnelles.             |");
	mvprintw(2*GRID_HEIGHT+Y_MARGIN+9,  X_MARGIN, "|Utilisez la touche backspace pour annuler le dernier déplacement.|");
	mvprintw(2*GRID_HEIGHT+Y_MARGIN+10, X_MARGIN, "|     Appuyez sur la touche enter pour quitter le programme.      |");
	mvprintw(2*GRID_HEIGHT+Y_MARGIN+11, X_MARGIN, "|-----------------------------------------------------------------|");
	attroff(COLOR_PAIR(3));
}


void drawWin(){
	move(2*GRID_HEIGHT+Y_MARGIN+3, X_MARGIN+2);
	clrtoeol();
	attron(A_REVERSE);
	printw("Victoire!");
	attroff(A_REVERSE);
}


void invalidMove(){
	move(2*GRID_HEIGHT+Y_MARGIN+4, X_MARGIN);
	printw("Action invalide");
}


void cannotMove(){
	move(2*GRID_HEIGHT+Y_MARGIN+4, X_MARGIN);
	printw("Deplacement impossible");
}


void drawEnd(){
	move(2*GRID_HEIGHT+Y_MARGIN+4, X_MARGIN);
	clrtoeol();
	printw("Partie terminée.");
	move(2*GRID_HEIGHT+Y_MARGIN+5, X_MARGIN);
	printw("Appuyer sur n'importe quelle touche pour quitter...");
	getch();
}
