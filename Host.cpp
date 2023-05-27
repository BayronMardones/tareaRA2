#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
//192.168.1.13 autodoxeo de pana banana
//192.168.0.16 nancu
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
      if ((cli_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
	  	  perror("socket failed");
	  	  exit(EXIT_FAILURE);
	    }
      else
      {
        cout << "CONGRATULATION :D" << endl;
      }

      serv_addr.sin_family = AF_INET;
	    serv_addr.sin_port = htons(PORT);
      serv_addr.sin_addr.s_addr = inet_addr(IP.c_str());

	    // Convert IPv4 and IPv6 addresses from text to binary
	    // form
	    // if (inet_pton(AF_INET, "192.168.1.13 ", &serv_addr.sin_addr) <= 0)
      // {
      //   cout << "Invalid address/ Address not supported " << endl;
	    // }

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

  void enviar()
  {
    send(cli_sockfd, hello, strlen(hello), 0);
    cout << "Hello message sent :D" << endl;
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
  cliente.enviar();

  cout << "fin" << endl;
  return 0;
}