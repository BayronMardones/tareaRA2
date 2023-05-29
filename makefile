all:
	g++ Host.cpp -o Host
	g++ Server.cpp -o Server

game:
	g++ game.cpp -o game

test:
	g++ test.cpp game.cpp -o test

clean:
	rm Host
	rm Server

cleangame:
	rm game

cleantest:
	rm test