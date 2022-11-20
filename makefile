compile:./main.cpp
	g++ -c ./main.cpp ./util/util.cpp ./util/gameManager.cpp ./util/ball.cpp ./util/playerbar.cpp -Iutil/libs/SFML-2.5.1/include/ -Lutil/libs/SFML-2.5.1/lib
	g++ main.o util.o gameManager.o ball.o playerbar.o -o bin/app -Iutil/libs/SFML-2.5.1/include/ -Lutil/libs/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
	del ball.o gameManager.o main.o playerbar.o util.o

run:
	./bin/app