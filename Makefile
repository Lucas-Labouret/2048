2048: 2048.o model.o ncurses_cli.o save.o common.o
	g++ -g 2048.o model.o ncurses_cli.o save.o common.o -o 2048 -lncurses

2048.o: 2048.cpp model.h ncurses_cli.h common.h
	g++ -c -g 2048.cpp

ncurses_cli.o: ncurses_cli.cpp common.h
	g++ -c -g ncurses_cli.cpp

model.o: model.cpp common.h
	g++ -c -g model.cpp

save.o: save.cpp save.h
	g++ -c -g save.cpp

common.o: common.cpp
	g++ -c -g common.cpp
