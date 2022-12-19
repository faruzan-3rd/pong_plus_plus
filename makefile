compile:./main.cpp
	g++ -std=c++17 -c ./main.cpp ./util/util.cpp ./util/gameManager.cpp ./util/ball.cpp ./util/paddle.cpp -Iutil/libs/SFML-2.5.1/include/ -Lutil/libs/SFML-2.5.1/lib -Iutil/include/ 
	g++ -std=c++17 main.o util.o gameManager.o ball.o paddle.o -o bin/app -Iutil/libs/SFML-2.5.1/include/ -Lutil/libs/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -Iutil/include/ 
	del ball.o gameManager.o main.o paddle.o util.o

run:
	./bin/app

yea:
	compile
	run