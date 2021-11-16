2048: 2048.o model.o ncurses_cli.o common.o
	g++ 2048.o model.o ncurses_cli.o common.o -o 2048 -lncurses

2048.o: 2048.cpp model.h ncurses_cli.h common.h
	g++ -c 2048.cpp

ncurses_cli.o: ncurses_cli.cpp common.h
	g++ -c ncurses_cli.cpp

model.o: model.cpp common.h
	g++ -c model.cpp

common.o: common.cpp
	g++ -c common.cpp
