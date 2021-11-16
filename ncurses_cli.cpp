#include <iostream>
#include <vector>
#include <ncurses.h>
#include <math.h>
#include <algorithm>
#include <stdexcept>

#include "model.h"

using namespace std;

const vector<int> VALID_KEYS = {KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_BACKSPACE, KEY_EXIT};


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
	return move;
}


int getUserInput(){
	/**Demande a l'utilisateur de saisir une action a effectuer
	**/
	int input = getch();
	return mapMove(input);
}


void draw(matrix grid){
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

	init_pair(1, COLOR_CYAN   , COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW , COLOR_BLACK);

	string sc = "";
	string head = "";
	string separator = "";

	string star = "*";
	string space = " ";
	
	clear();

	move(0,0);
	sc = to_string(score(grid));

	attron(COLOR_PAIR(1));
	printw("Score: ");
	attroff(COLOR_PAIR(1)); attron(COLOR_PAIR(2));
	printw(sc.c_str());
	attroff(COLOR_PAIR(2));

	separator =  (star * (GRID_WIDTH+1)) 
		        +(star * max_len * GRID_WIDTH);

	attron(COLOR_PAIR(1));
	if (separator.size()%2 == 0){
		mvprintw(1, 0, ( star * (separator.size()/2 - 2) ).c_str());
	} else {
		mvprintw(1, 0, ( star * (separator.size()/2 - 1) ).c_str());
	}
	attroff(COLOR_PAIR(1)); attron(COLOR_PAIR(2));
	printw("2048");
	attroff(COLOR_PAIR(2)); attron(COLOR_PAIR(1));
	printw( (star * (separator.size()/2 - 2)).c_str() );
	attroff(COLOR_PAIR(1));

	for (int y = 0; y < GRID_HEIGHT; y++){
		move(2+y,0);
		for (int x = 0; x < GRID_WIDTH; x++){
			string cell = strGrid[y][x];
			attron(COLOR_PAIR(1));
			printw((star + (space * ((max_len-cell.size())/2))).c_str());
			attroff(COLOR_PAIR(1));

			if (grid[y][x] != 0){
				int delta = 25*(static_cast<int>(log2(grid[y][x])-1));
				init_color(COLOR_RED, 1000, max(0,1000-delta), max(0,1000-delta));
				init_pair(3, COLOR_RED, COLOR_BLACK);
			}
			attron(COLOR_PAIR(3));
			printw(cell.c_str());
			attron(COLOR_PAIR(3));

			attron(COLOR_PAIR(1));
			if ((max_len-cell.size())%2 == 0){
				printw((space * (((max_len-cell.size()))/2)).c_str());
			} else {
				printw((space * ((max_len-cell.size())/2 + 1)).c_str());
			}
			attroff(COLOR_PAIR(1));
			
		}
		attron(COLOR_PAIR(1));
		printw((star + "\n" + separator).c_str());
		attroff(COLOR_PAIR(1));
	}
	attron(COLOR_PAIR(4));
	mvprintw(GRID_HEIGHT+7,  0, "|--------------------------Instructions---------------------------|");
	mvprintw(GRID_HEIGHT+8,  0, "|             Jouez avec les flèches directionnelles.             |");
	mvprintw(GRID_HEIGHT+9,  0, "|Utilisez la touche backspace pour annuler le dernier déplacement.|");
	mvprintw(GRID_HEIGHT+10, 0, "|     Appuyez sur la touche enter pour quitter le programme.      |");
	mvprintw(GRID_HEIGHT+11, 0, "|-----------------------------------------------------------------|");
	attroff(COLOR_PAIR(4));
}


void drawWin(){
	move(GRID_HEIGHT+3, 2);
	clrtoeol();
	attron(A_REVERSE);
	printw("Victoire!");
	attroff(A_REVERSE);
}


void invalidMove(){
	move(GRID_HEIGHT+4, 0);
	printw("Action invalide");
}


void cannotMove(){
	move(GRID_HEIGHT+4, 0);
	printw("Deplacement impossible");
}


void drawEnd(){
	move(GRID_HEIGHT+4, 0);
	clrtoeol();
	printw("Partie terminée.\nAppuyer sur n'importe quelle touche pour quitter...");
	getch();
}
