#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
//si
#define PORT 8080

using namespace std;

class Server
{
  public: 
    int sockfd, new_sockfd, opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char buffer[1024] = { 0 };
    int valread;

    Server()
    {
      if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
	  	  perror("socket failed");
	  	  exit(EXIT_FAILURE);
	    }
      else
      {
        cout << "CONGRATULATION :D" << endl;
      }
  
      if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
      {
	    	perror("setsockopt");
	    	exit(EXIT_FAILURE);
	    }
      else
      {
        cout << "CONFIGURED SOCKET :D" << endl;
      }
  
      address.sin_family = AF_INET;
	    address.sin_addr.s_addr = INADDR_ANY;
	    address.sin_port = htons(PORT);
  
	    // Forcefully attaching socket to the port 8080
	    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0)
      {
	    	perror("bind failed");
	    	exit(EXIT_FAILURE);
	    }
      else
      {
        cout << "CONFIGURED BIND :D" << endl;
      }
  
      if (listen(sockfd, 3) < 0)
      {
	  	  perror("listen");
	  	  exit(EXIT_FAILURE);
	    }
      else
      {
        cout << "LISTEN CORRECT :D" << endl;
      }
  
      if ((new_sockfd = accept(sockfd, (struct sockaddr*)&address, 
      (socklen_t*)&addrlen)) < 0)
      {
	  	  perror("accept");
	  	  exit(EXIT_FAILURE);
	    }
      else
      {
        cout << "SERVER FINISHED :D" << endl;
      }

  }

  void recibir(){
    valread = read(new_sockfd, buffer, 1024);
	  printf("%s\n", buffer);
  }

};

int main()
{

  cout << "STARTING" << endl;
  Server socket;
  socket.recibir();

  cout << "BYE ;)" << endl;

  return 0;
}