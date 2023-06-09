#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

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
        cout << "Conexion establecida, espere la respuesta del servidor..." << endl;
      }
		  
		
	}

  //metodo que envia un mensaje al servidor
  void action()
  {
    //leer mensaje del server
    int bytesRead = read(cli_sockfd, buffer, sizeof(buffer));
    if (bytesRead < 0) {
        cerr << "Error al leer datos del servidor" << endl;
        close(cli_sockfd);
    }
    cout << buffer << endl;


    //enviar respuesta al server
    while(true) {
      cout << "Ingrese las coordenadas(ejemplo: 2,3): ";
      string message;
      getline(cin, message);

      int bytesSent = send(cli_sockfd, message.c_str(), message.length(), 0);
      if (bytesSent < 0) {
        std::cerr << "Error al enviar el mensaje al servidor" << std::endl;
        close(cli_sockfd);
      }
      if(message == "exit") break;
    }
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

  cliente.action();
  cout << "fin" << endl;
  return 0;
}