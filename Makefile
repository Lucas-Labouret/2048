2048: 2048.o model.o ncurses_cli.o
	g++ 2048.o model.o ncurses_cli.o -o 2048 -lncurses

2048.o: 2048.cpp
	g++ -c 2048.cpp

ncurses_cli.o: ncurses_cli.cpp
	g++ -c ncurses_cli.cpp

model.o: model.cpp
	g++ -c model.cpp
