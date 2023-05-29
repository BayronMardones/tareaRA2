all:
	g++ Host.cpp -o Host
	g++ Server.cpp game.cpp -o Server

clean:
	rm Host
	rm Server