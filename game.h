#ifndef GAME_H
#define GAME_H

class Game {
  public:
    char tablaServer[15][15];
    char tablaHost[15][15];
    int puntajeHost;
    int puntajeServer;
    char turno;

    Game();

    void fillServer();

    void disparoServer();

    void disparo(int x, int y);

    int getPuntajeHost();

    int getPuntajeServer();

    char getTurno();

    int checkBoat(int a, int b, int o, int l, char tabla);

    void randomBoat(int largo, char tipo);

    void putBoatServer(int a, int b, int largo, int orientacion, char tipo);

    void putBoatHost(int a, int b, int largo, int orientacion, char tipo);

    void showServer();

    void showHost();
};

#endif