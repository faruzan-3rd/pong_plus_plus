compile:./main.cpp
	g++ -c ./main.cpp ./util/util.cpp ./util/gameManager.cpp ./util/ball.cpp ./util/playerbar.cpp
	g++ main.o util.o gameManager.o ball.o playerbar.o -o app -lsfml-graphics -lsfml-window -lsfml-system
	rm -f ball.o gameManager.o main.o playerbar.o util.o

run:
	./app