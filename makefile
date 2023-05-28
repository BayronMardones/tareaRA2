all:
	g++ Host.cpp -o Host
	g++ Server.cpp -o Server

game:
	g++ game.cpp -o game

clean:
	rm Host
	rm Server

cleangame:
	rm game