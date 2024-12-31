/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

/*  移除老的服务端套接字，并创建一个新的未命名套接字.  */

    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  命名套接字.  */

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    //套接字应该存储了地址、端口这些信息，从这句可以看出来
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  创建一个连接队列，并且等待客户端连接.  */

    listen(server_sockfd, 5);
    while(1) {
        char ch;

        printf("server waiting\n");

/*  接受一个客户端连接.  */

	//client_address的值从哪里来
        client_len = sizeof(client_address);
	//创建了一个新的套接字用于数据传输，套接字是给程序用的用于跟操作系统交互数据的符号
        client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);

/*  读写socket.  */

        read(client_sockfd, &ch, 1);
        ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }
}


