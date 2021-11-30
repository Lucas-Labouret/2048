2048: 2048.o model.o ncurses_cli.o save.o ai_player.o common.o
	g++ -g 2048.o model.o ncurses_cli.o save.o ai_player.o common.o -o 2048 -lncurses

2048.o: 2048.cpp model.h ncurses_cli.h common.h
	g++ -c -g 2048.cpp

ncurses_cli.o: ncurses_cli.cpp common.h
	g++ -c -g ncurses_cli.cpp

model.o: model.cpp common.h
	g++ -c -g model.cpp

save.o: save.cpp save.h
	g++ -c -g save.cpp

ai_player.o: ai_player.cpp ai_player.h
	g++ -c -g ai_player.cpp

common.o: common.cpp common.h
	g++ -c -g common.cpp
