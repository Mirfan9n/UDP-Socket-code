THis is basic Client Server UDP COD
client -> Socket()
          bind() <- Not nessary
          while( // condition ) {
            recvfrom(fd, *buffer, sizeof(buffer), flags , (const struct sockaddr*)&server_addr, sizeof(server_addr))
            sendto( //same  )
          }
close(fd)
