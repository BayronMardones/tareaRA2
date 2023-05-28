#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <time.h>
//si
// #define PORT 8080

using namespace std;

class Game {
  public:
    char tablaServer[15][15];
    char tablaHost[15][15];
    int puntajeHost;
    int puntajeServer;
    char turno;

    Game() {
      for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
          tablaServer[i][j] = '_';
          tablaHost[i][j] = '_';
        }
      }
      puntajeHost = 0;
      puntajeServer = 0;
      if(rand() % 2 == 0) turno = 's';
      else turno = 'h';
    }

    void fillServer() {
      randomBoat(5, 'P');
      randomBoat(4, 'B');
      randomBoat(4, 'B');
      randomBoat(3, 'S');
      randomBoat(3, 'S');
      randomBoat(1, 'L');
      randomBoat(1, 'L');
      randomBoat(1, 'L');
    }

    void disparoServer() {
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

    void disparo(int x, int y) {
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

    int getPuntajeHost() {
      return puntajeHost;
    }

    int getPuntajeServer() {
      return puntajeServer;
    }

    char getTurno() {
      return turno;
    }

    int checkBoat(int a, int b, int o, int l, char tabla) {
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

    void randomBoat(int largo, char tipo) {
      int x, y, o;
      o = rand() % 2;
      x = rand() % 15;
      y = rand() % 15;

      if(o == 1)
        do {
          y = rand() % 15;
        } while(y > 10 || checkBoat(x, y, o, largo, 's'));
      if(0 == 0)
        do {
          x = rand() % 15;
        } while(x > 10 || checkBoat(x, y, o, largo, 's'));
      putBoatServer(x, y, largo, o, tipo);
    }

    void putBoatServer(int a, int b, int largo, int orientacion, char tipo) {
      if(orientacion == 0) {
        for(int i = a; i < largo + a; i++)
          tablaServer[i][b] = tipo;
      }
      if(orientacion == 1) {
        for(int i = b; i < largo + b; i++)
          tablaServer[a][i] = tipo;
      }
    }

    void putBoatHost(int a, int b, int largo, int orientacion, char tipo) {
      if(orientacion == 0) {
        for(int i = a; i < largo + a; i++)
          tablaHost[i][b] = tipo;
      }
      if(orientacion == 1) {
        for(int i = b; i < largo + b; i++)
          tablaHost[a][i] = tipo;
      }
    }

    void showServer() {
      for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
          cout << " | " << tablaServer[i][j];
        }
        cout << " |" << endl;
      }
    }

    void showHost() {
      for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
          cout << " | " << tablaHost[i][j];
        }
        cout << " |" << endl;
      }
    }
};

int main(int argc, char *argv[])
{
  srand(time(0));
  Game partida;
  partida.fillServer();
  cout << endl;
  partida.showServer();
  partida.disparo(3, 3);
  cout << endl;
  partida.showServer();

  return 0;
}