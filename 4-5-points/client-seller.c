#include <stdio.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <stdlib.h> 
#include <string.h>   
#include <unistd.h>    

#define RCVBUFSIZE 8 
#define MAXPENDING 5   

// Логика работы продавца
void seller(int id) {
    printf("Seller %d PID: %d\n", id, getpid());

    printf("Selling stock with id=%d\n",  id);
    sleep(1);

    printf("Seller %d finished\n", id);
}

void HandleTCPClient(int clntSocket)
{
    printf("ndnlng");
    char echoBuffer[RCVBUFSIZE];        
    int recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0);

    seller(4);

    close(clntSocket);
}

int main(int argc, char *argv[])
{
    int servSock;                   
    int clntSock;                   
    struct sockaddr_in echoServAddr; 
    struct sockaddr_in echoClntAddr;
    unsigned short echoServPort;   
    unsigned int clntLen;   

    echoServPort = 50226;

    servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&echoServAddr, 0, sizeof(echoServAddr));  
    echoServAddr.sin_family = AF_INET;               
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);    

    bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr));
    listen(servSock, MAXPENDING);

    for (;;)
    {
        clntLen = sizeof(echoClntAddr);

        clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen);
        printf("alive\n");

        HandleTCPClient(clntSock);
    }
}
