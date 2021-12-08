all:
	make --no-print-directory 2048_IA
	make --no-print-directory ai_trainer
	make --no-print-directory test
	make --no-print-directory 2048



clean:
	rm *.o 2048_IA ai_trainer test 2048




2048_IA: modele.o ai_player.o 2048_IA.o common.o
	g++ -g modele.o ai_player.o common.o 2048_IA.o -o 2048_IA

2048_IA.o: 2048_IA.cpp
	g++ -c -g 2048_IA.cpp



ai_trainer: ai_player.o ai_trainer.o
	g++ -g modele.o ai_player.o ai_trainer.o common.o -o ai_trainer

ai_trainer.o: ai_trainer.cpp modele.h common.h
	g++ -c -g ai_trainer.cpp



test: modele.o test.o common.o
	g++ -g test.o modele.o common.o -o test

test.o: test.cpp modele.h
	g++ -c -g test.cpp



2048: 2048.o modele.o ncurses_cli.o save.o ai_player.o common.o
	g++ -g 2048.o modele.o ncurses_cli.o save.o ai_player.o common.o -o 2048 -lncurses

2048.o: 2048.cpp modele.h ncurses_cli.h common.h
	g++ -c -g 2048.cpp

ncurses_cli.o: ncurses_cli.cpp common.h
	g++ -c -g ncurses_cli.cpp

modele.o: modele.cpp common.h
	g++ -c -g modele.cpp

save.o: save.cpp save.h common.h
	g++ -c -g save.cpp

ai_player.o: ai_player.cpp ai_player.h common.h
	g++ -c -g ai_player.cpp

common.o: common.cpp common.h
	g++ -c -g common.cpp
