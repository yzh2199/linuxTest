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
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch = 'A';

/*  创建socket.  */

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

/*  命名socket, as agreed with the server.  */

    // 这句是在干嘛，答案是在设置socket域
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

/*  连接到server端socket.  */

    //这一句就是在主动连接服务端，所以客户端是知道服务端的套接字地址的，可以看到address在上面被设置里地址server_socket，这就是server1套接字的地址
    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
	//没启动server1时，运行失败后会报oops: client1:no such file or direction，因为没创建服务端套接字
        perror("oops: client1");
        exit(1);
    }

/*  通过socketfd进行读写.  */

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);
    exit(0);
}
