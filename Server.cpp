#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <pthread.h>
#include <cstring>
#include <string>
#include "game.h"
//si

using namespace std;
const int MAX_CLIENTS = 5;

void* HandleClient(void* arg) {

  // Lógica para manejar la conexión con el cliente
  char buffer[1024];
  static int clientCounter = 0;
  int clientNumber = ++clientCounter;
  int clientSocket = *(static_cast<int*>(arg));

  cout << "Cliente "<< "[ " << clientNumber << " ] conectado" << endl;

  //inicializacion de la partida
  Game partida;
  partida.fillServer();
  partida.fillHost();

  //enviar mensaje al cliente
  const char* message = "Bienvenido al servidor, solicitud de coordenadas.";
  write(clientSocket, message, strlen(message));
  cout<< "mensaje enviado al cliente: "<< clientNumber <<endl;

  int status = 1;
  while(status) {
    cout << "tabla del server" << endl;
    partida.showServer();
    cout << endl;
    cout << "tabla del cliente" << endl;
    partida.showHost();
    if(partida.getTurno() == 's') {
      cout << "turno del server" <<  endl;
      partida.disparoServer();
    }
    else {
      cout << "turno del cliente" << endl;
      int bytesRead = read(clientSocket, buffer, sizeof(buffer));
      int coma = 0;
      string aux = buffer;
      string aux1 = "", aux2 = "";
      for(int i = 0; aux[i] != '\n'; i++) {
        if(aux[i] == ',') coma = 1;
        if(coma == 0) aux1 += aux[i];
        else aux2 += aux[i];
      }
      int x = stoi(aux1), y = stoi(aux2);
      cout << x << " " << y << endl;
      partida.disparo(x, y);
      memset(buffer, 0, sizeof(buffer));
    }
    cout << endl;
    cout << "puntaje cliente: " << partida.getPuntajeHost() << " puntaje server: " << partida.getPuntajeServer() << endl;
    if(partida.getPuntajeHost() == 22 || partida.getPuntajeServer() == 22) {
      status = 0;
    }
  }

  //escuchar respuesta del cliente
  
  // Cerrar el socket del cliente
  close(clientSocket);
  cout << "Cliente "<< "[ " << clientNumber << " ] desconectado" << endl;
  pthread_exit(NULL);
  
}

int main(int argc, char *argv[])
{

 //verificar que se agregue la cantidad de datos correctos desde la terminal
  if (argc != 2)
  {
    cerr << "Usage: " << argv[0] << " <PORT>" << endl;
    return 1;
  }
  int PORT = atoi(argv[1]);
  cout << "STARTING" << endl;

  int sockfd, new_sockfd, opt = 1, valread;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  char buffer[1024] = { 0 };

  //creacion del socket
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
	  perror("socket failed");
	  exit(EXIT_FAILURE);
	}

  //configuracion del socket
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

  address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	// enlace del socket al puerto ingresado
	if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0)
  {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

//socket en modo escucha esperando a que entre el socket cliente
  if (listen(sockfd, 3) < 0)
  {
	  perror("listen");
	  exit(EXIT_FAILURE);
	}
  else
  {
    cout << "Esperando conexiones..." << endl;
  }

  while(true)
  {
    //acepta el socket entrante y verifica que este 
    if ((new_sockfd = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
	    perror("accept");
	    exit(EXIT_FAILURE);
	  }
    else
    {
      cout << "SERVER FINISHED :D" << endl;
    }

    pthread_t sockfdThread;
    if (pthread_create(&sockfdThread, NULL, HandleClient, &new_sockfd) != 0)
    {
      cerr << "Error al crear el hilo para el cliente" << endl;
      close(new_sockfd);
      continue;
    }
    pthread_detach(sockfdThread);
  }

  cout << "BYE ;)" << endl;
  return 0;
}