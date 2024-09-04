#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>



int main(){

    int cli_fd;
    struct sockaddr_in server_a;
    socklen_t len = sizeof(server_a);
    char buffer[1024];
    int counter = 0;

    if((cli_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Cant Create a Server File descritor");
        exit(EXIT_FAILURE);
    }


    server_a.sin_port = htons(8080);  
    server_a.sin_family = AF_INET;
    server_a.sin_addr.s_addr= inet_addr("127.0.0.1");

    const char *message = "HELLO JI ~FROM CLI";

    while(counter < 2 ){

        sendto(cli_fd, message, strlen(message), 0, (struct sockaddr *)&server_a, len);
        // printf("DATA sent to server from CLI \n" );


        int recvLen = recvfrom(cli_fd, buffer, sizeof(buffer), 0, 
        (struct sockaddr*)&server_a, &len );
        
        if(recvLen < 0){
            perror("Data din't got received in CLI \n");
            break;
        }
        buffer[recvLen] = '\0';  // Null-terminate the received data
        printf("DATA recieved in CLI: %s \n", buffer );

        counter++;
    }

    close(cli_fd);


    return 0;
}