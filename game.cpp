#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "game.h"
//si
// #define PORT 8080

using namespace std;

//constructor de la partida
Game::Game() {
  for(int i = 0; i < 15; i++) {
    for(int j = 0; j < 15; j++) {
      tablaServer[i][j] = '_';
      tablaHost[i][j] = '_';
    }
  }
  puntajeHost = 0;
  puntajeServer = 0;
  srand(time(0));
  if(rand() % 2 == 0) turno = 's';
  else turno = 'h';
}


//llenado de la tabla del server de manera aleatoria
void Game::fillServer() {
  cout << "filling server table, please wait" << endl;
  randomBoat(5, 'P');
  cout << "P READY" << endl;
  randomBoat(4, 'B');
  cout << "B1 READY" << endl;
  randomBoat(4, 'B');
  cout << "B2 READY" << endl;
  randomBoat(3, 'S');
  cout << "S1 READY" << endl;
  randomBoat(3, 'S');
  cout << "S2 READY" << endl;
  randomBoat(1, 'L');
  cout << "L1 READY" << endl;
  randomBoat(1, 'L');
  cout << "L2 READY" << endl;
  randomBoat(1, 'L');
  cout << "L3 READY" << endl;
}


//disparo del server de manera aleatoria
void Game::disparoServer() {
  int x, y;
  do {
    int x = rand() % 15;
    int y = rand() % 15;
  } while(tablaHost[x][y] == 'X' || tablaHost[x][y] == 'O');
  if(tablaHost[x][y] != '_') {
    puntajeServer++;
    tablaHost[x][y] = 'O';
    cout << "acierto" << endl;
  }else {
    tablaHost[x][y] = 'X';
    cout << "fallo" << endl;
  }
  turno = 'h';
}

//disparo del cliente
void Game::disparo(int x, int y) {
  if(tablaServer[x][y] != '_') {
    puntajeHost++;
    tablaServer[x][y] = 'O';
    cout << "acierto" << endl;
  }else {
    tablaServer[x][y] = 'X';
    cout << "fallo" << endl;
  }
  turno = 's';
}

//retorna el puntaje del cliente
int Game::Game::getPuntajeHost() {
  return puntajeHost;
}

//retorna el puntaje del server
int Game::getPuntajeServer() {
  return puntajeServer;
}

//retorna el turno de juego
char Game::getTurno() {
  return turno;
}

//comprueba que el espacio donde sera colocado el barco este limpio
int Game::checkBoat(int a, int b, int o, int l, char tabla) {
  if(tabla == 's') {
    if(o == 0) {
      for(int i = a; i < l + a; i++)
        if(tablaServer[i][b] != '_')
        return 1;
    }
    if(o == 1) {
      for(int i = b; i < l + b; i++)
        if(tablaServer[a][i] != '_')
        return 1;
    }
  }
  if(tabla == 'h') {
    if(o == 0) {
      for(int i = a; i < l + a; i++)
        if(tablaHost[i][b] != '_')
        return 1;
    }
    if(o == 1) {
      for(int i = b; i < l + b; i++)
        if(tablaHost[a][i] != '_')
        return 1;
    }
  }
  return 0;
}

//agrega botes de manera aleatoria
void Game::randomBoat(int largo, char tipo) {
  int x, y, o;
  o = rand() % 2;
  x = rand() % 15;
  y = rand() % 15;

  if(o == 1)
    do {
      y = rand() % 15;
    } while(y > 10 || checkBoat(x, y, o, largo, 's'));
  if(o == 0)
    do {srand(time(0));
      x = rand() % 15;
    } while(x > 10 || checkBoat(x, y, o, largo, 's'));
  putBoatServer(x, y, largo, o, tipo);
}

//agrega un bote a la tabla de server
void Game::putBoatServer(int a, int b, int largo, int orientacion, char tipo) {
  if(orientacion == 0) {
    for(int i = a; i < largo + a; i++)
      tablaServer[i][b] = tipo;
  }
  if(orientacion == 1) {
    for(int i = b; i < largo + b; i++)
      tablaServer[a][i] = tipo;
  }
}

//agrega un bote a la tabla de cliente
void Game::putBoatHost(int a, int b, int largo, int orientacion, char tipo) {
  if(orientacion == 0) {
    for(int i = a; i < largo + a; i++)
      tablaHost[i][b] = tipo;
  }
  if(orientacion == 1) {
    for(int i = b; i < largo + b; i++)
      tablaHost[a][i] = tipo;
  }
}

//muetra la tabla del server
void Game::showServer() {
  for(int i = 0; i < 15; i++) {
    for(int j = 0; j < 15; j++) {
      cout << " | " << tablaServer[i][j];
    }
    cout << " |" << endl;
  }
}

//muestra la tabla del cliente
void Game::showHost() {
  for(int i = 0; i < 15; i++) {
    for(int j = 0; j < 15; j++) {
      cout << " | " << tablaHost[i][j];
    }
    cout << " |" << endl;
  }
}
