#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>


//192.168.1.13 autodoxeo de pana banana
// #define PORT 8080

using namespace std;

class Client
{
  public:
    int cli_sockfd, status;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    const char* hello = "Hello from client";

    Client(const string& IP, int PORT)
    {
      //creaccion  del socket
      if ((cli_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
	  	  perror("socket failed");
	  	  exit(EXIT_FAILURE);
	    }
      else
      {
        cout << "CONGRATULATION :D" << endl;
      }

      //establecer conexion con el socket del servidor y entrega de datos de la estructura sockaddr
      serv_addr.sin_family = AF_INET;
	    serv_addr.sin_port = htons(PORT);
      serv_addr.sin_addr.s_addr = inet_addr(IP.c_str());

      if (connect(cli_sockfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
      {
        perror("listen");
	  	  exit(EXIT_FAILURE);
      }
      else
      {
        cout << "connection finished :D" << endl;
      }
		  
		
	}

  //metodo que envia un mensaje al servidor
  void escuchar()
  {

    int bytesRead = read(cli_sockfd, buffer, sizeof(buffer));
    if (bytesRead < 0) {
        cerr << "Error al leer datos del servidor" << endl;
        close(cli_sockfd);
    }
    cout << "Mensaje recibido: " << buffer << endl;

    // string mensaje;
    // cout << "Ingrese su mensaje: ";
    // getline(cin, mensaje);
    // send(cli_sockfd, hello, strlen(hello), 0);
    // cout << "Mensaje enviado" << endl;
  }

};

int main(int argc, char *argv[])
{

  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <variable1> <variable2>" << endl;
    return 1;
  }

  
  string IP = argv[1];
  int PORT = atoi(argv[2]);

  Client cliente(IP, PORT);

  //cliente.acciones();
  cliente.escuchar();
  cout << "fin" << endl;
  return 0;
}