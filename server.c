#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){

    int server_fd;
    struct sockaddr_in server_a, cli_a;
    socklen_t len = sizeof(cli_a);
    char buffer[1024];
    int counter = 0;

    if((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Cant Create a Server File descritor");
        exit(EXIT_FAILURE);
    }

    // bind the server

    server_a.sin_port = htons(PORT);  // make sure to convert into network
    server_a.sin_family = AF_INET;
    server_a.sin_addr.s_addr= INADDR_ANY;

    if(bind(server_fd, (const struct sockaddr*)&server_a, sizeof(server_a)) < 0){
        perror("Conot Bind the Server_fb");
        close(server_fd); // make sure to close itsizeof(cli_a)
        exit(EXIT_FAILURE);
    }

   while(counter < 2) {
        int recvLen = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cli_a, &len);

        if(recvLen < 0) {
            perror("Data didn't get received in server");
            break;
        }

        buffer[recvLen] = '\0';  // Null-terminate the received data

        // Convert the client's IP address to a readable format
        char cli_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(cli_a.sin_addr), cli_ip, INET_ADDRSTRLEN);
        
        int portNo = ntohs(cli_a.sin_port);
        
        printf("DATA received in server FROM CLI IP ->> %s \n: Cli PORT: %d\n" , cli_ip, portNo);
        printf("SERver BUFFER Message: %s \n", buffer);

        const char *message = "HELLO JI ~FROM SERVER";

        sendto(server_fd, message, strlen(message), 0, (struct sockaddr *)&cli_a, len);

        // printf("DATA sent to client from server\n");
        counter++;
    }

    close(server_fd);


    return 0;
}