#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

//编译指令
// arm-rockchip830-linux-uclibcgnueabihf-gcc -o socketClient socketClient.c
// chmod +x gpiotest
// ./gpiotest
//scp /home/ubuntu/study2024/myproject/w4_socket/socketClient  root@192.168.2.126:/root/socketClient

#define SERVER_PORT 9902 //服务器的端口号 
//#define SERVER_IP "192.168.8.50" //服务器的IP地址
#define SERVER_IP "172.32.0.100"

int main(void)
{
	struct sockaddr_in server_addr = {0}; 
	char buf[512]; 
	int sockfd; 
	int ret;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > sockfd) {
		printf("socket error");
		exit(EXIT_FAILURE);
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT); //端口号
	inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);//IP地址
	
	ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));if (0 > ret) {
		printf("connect error");
		close(sockfd); 
		exit(EXIT_FAILURE); 
	}
	printf("服务器连接成功...\n\n");
	/* 向服务器发送数据 */
	for ( ; ; ) {
		// 清理缓冲区 
		memset(buf, 0x0, sizeof(buf));
		// 接收用户输入的字符串数据
		printf("Please enter a string: ");
		fgets(buf, sizeof(buf), stdin);
		// 将用户输入的数据发送给服务器
		ret = send(sockfd, buf, strlen(buf), 0); 
		if(0 > ret){
			printf("send error"); 
			break; 
		}
		//输入了"exit"，退出循环
		if(0 == strncmp(buf, "exit", 4)) 
			break;
	}
	close(sockfd);
	exit(EXIT_SUCCESS);	
}
