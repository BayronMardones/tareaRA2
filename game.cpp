#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
//si
// #define PORT 8080

using namespace std;

class Game {
  public:

};

class Boat {
  public:
    int largo;
    int x;
    int y;
    int orientacion;
    int status;
    
    Boat(int a, int b, int l, int o) {
      largo = l;
      x = a;
      y = b;
      orientacion = o;
      status = 1;
    }

    void setBoat(int a, int b, int l, int o) {
      largo = l;
      x = a;
      y = b;
      orientacion = o;
    }

    int getLargo() {
      return largo;
    }

    int getOrientacion() {
      return orientacion;
    }

    int getX(){
      return x;
    }

    int getY(){
      return y;
    }

    void showBoat() {
      cout << "largo: " << largo << " (x,y): (" << x << "," << y << ") orientacion: " << orientacion << " status: " << status <<  endl;
    }
};

class Tables {
  public:
    int tablaServer[15][15];
    int tablaCliente[15][15];

    void setServer() {

    }


};

int main(int argc, char *argv[])
{
  Boat bote1(1, 1, 5, 0);
  bote1.showBoat();
  return 0;
}