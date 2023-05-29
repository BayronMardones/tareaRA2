#include <iostream>
#include "game.h"

using namespace std;

int main() {
  Game partida;
  partida.fillServer();
  cout << endl;
  partida.showServer();
  partida.disparo(3, 3);
  cout << endl;
  partida.showServer();

  return 0;
}