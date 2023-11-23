#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100

void error_handling(char *message);
void CutTokens(char* str);
void display();
void Forward(char *str, int sender) ;
int GetEmptySlot();

char tokens[3][100];
#define MAXCLIENT (16)
int peertcpSocket[MAXCLIENT];	// max 128 clients


int main(int argc, char **argv) {
	
  int tcpServ_sock;
  int slot;
  
  struct sockaddr_in tcpServer_addr;
  struct sockaddr_in tcpClient_addr;
  struct sockaddr_in newTcp_addr;
  for(int i = 0; i < MAXCLIENT; i++) {
  	peertcpSocket[i] = -1;;	// max 128 clients
    
  }

  socklen_t clnt_len;
    
  fd_set reads, temps;
  int fd_max;

  char *tcpport = NULL;
  
  char str[BUFSIZE];
  int option = 2;

  if(argc != 2) {
    printf("Usage : %s <tcpport> \n", argv[0]);
    exit(1);
  }

  tcpport = argv[1];

  display();
	
  tcpServ_sock = socket(AF_INET, SOCK_STREAM, 0);
  if(tcpServ_sock == -1)
	  error_handling("socket() error");
  
  memset(&tcpServer_addr, 0 , sizeof(tcpServer_addr));
  tcpServer_addr.sin_family = AF_INET;
  tcpServer_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  tcpServer_addr.sin_port = htons(atoi(tcpport));

  setsockopt(tcpServ_sock, SOL_SOCKET, SO_REUSEADDR, (const void *)&option, sizeof(int));
  setsockopt(tcpServ_sock, SOL_SOCKET, SO_REUSEPORT, (const void *)&option, sizeof(int));
  if( bind(tcpServ_sock, (struct sockaddr *) &tcpServer_addr, sizeof(tcpServer_addr)) == -1 )
	  error_handling("bind() error");

			
  if(listen(tcpServ_sock, 5)==-1)
    error_handling("listen() error");
  
  FD_ZERO(&reads);
  FD_SET(tcpServ_sock, &reads);
  fd_max = tcpServ_sock;

  while(1) {
    int nfound = 0;

    temps = reads;
    
    nfound = select(fd_max+1, &temps, 0, 0, NULL);
	
	if(FD_ISSET(tcpServ_sock, &temps)) {
		// Input from the client for new connection
		// This request will arrive after UDP sent
  		FD_CLR(tcpServ_sock, &temps);

		clnt_len = sizeof(newTcp_addr);
        slot = GetEmptySlot();
		peertcpSocket[slot] = accept(tcpServ_sock, 
			(struct sockaddr *)&newTcp_addr, &clnt_len);

		printf("connection from host %s, port %d, socket %d slot %d\n",
                        inet_ntoa(newTcp_addr.sin_addr),  
                        ntohs(newTcp_addr.sin_port), peertcpSocket[slot], slot);

		sprintf(str, "Welcome: host %s, port %d\n", 
				inet_ntoa(newTcp_addr.sin_addr),  ntohs(newTcp_addr.sin_port));
		write(peertcpSocket[slot], str, strlen(str));

		FD_SET(peertcpSocket[slot], &reads);
		if(fd_max < peertcpSocket[slot])
			fd_max = peertcpSocket[slot];
	} else {
		for(int i = 0; i < MAXCLIENT; i++) {
		  if (FD_ISSET(peertcpSocket[i], &temps)) {
			FD_CLR(peertcpSocket[i], &temps);

			/* process the data */
			int bytesread = read(peertcpSocket[i], str, sizeof str - 1);
			if (bytesread<0) {
				perror("read");
				/* fall through */
			}
			if (bytesread <= 0) {
				printf("Connection Closed %d slot %d\n", 
					peertcpSocket[i], i);
				FD_CLR(peertcpSocket[i], &reads);
				if (close(peertcpSocket[i])) perror("close");
				peertcpSocket[i] = -1;
				continue;
			}
            str[bytesread] = 0;	

           // forward the message to all the other sockets
           Forward(str, i);
          }
		}
	}

  }//while End
}//main End

void display() {
	printf("Student ID : 20000000 \n");
	printf("Name : Sanghwan  \n");
}

void error_handling(char *message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  perror("hi");
  exit(1);
}

void CutTokens(char* str) {
	char *pch;
	int cnt = 0;

	pch = strtok(str, " \r\n\t");
	
	while(pch != NULL) {
		strcpy(tokens[cnt++], pch);
		pch = strtok(NULL, " ");
	}
}


void Forward(char *str, int sender) {
  for(int i = 0; i < MAXCLIENT; i++) {
     if((peertcpSocket[i] != -1) && (i != sender)) {
		write(peertcpSocket[i], str, strlen(str));
	 }
  }
}

int GetEmptySlot() {
  for(int i = 0; i < MAXCLIENT; i++) {
     if(peertcpSocket[i] == -1) return i;
  }
  return -1;
}

