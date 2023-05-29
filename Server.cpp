#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <pthread.h>
#include <cstring>
//si
// #define PORT 8080

using namespace std;
const int MAX_CLIENTS = 5;

void* HandleClient(void* arg) {
  char buffer[1024];
  static int clientCounter = 0;
  int clientNumber = ++clientCounter;
  int clientSocket = *(static_cast<int*>(arg));
  cout << "Cliente " << clientNumber << " conectado" << endl;

 
  const char* message = "Hola, cliente!";
  write(clientSocket, message, strlen(message));
  cout<< "mensaje enviado al cliente"<< clientNumber <<endl;

 

  // Lógica para manejar la conexión con el cliente
  // Cerrar el socket del cliente
  close(clientSocket);
  pthread_exit(NULL);
}

  //metodo que lee el contenido del socket cliente guardado en buffer
  // void recibir(int valread){
  //   valread = read(new_sockfd, buffer, 1024);
	//   printf("%s\n", buffer);
  // }

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