#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 3000

int main(int argc, char* argv[]){
	int server_fd,new_socket,valread;
	struct sockaddr_in address;
	int opt=1;
	int addrlen=sizeof(address);
	char buffer[1024]={0};
	char *hello="Hello from server";

	//socket file descriptor
	if((server_fd=socket(AF_INET,SOCK_STREAM,0)) == 0){
		perror("server socket failed");
		exit(EXIT_FAILURE);
	}
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port=htons(PORT);

	if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if(listen(server_fd,3)<0){
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
	if((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0){
		perror("accept error");
		exit(EXIT_FAILURE);
	}
	valread=read(new_socket,buffer,1024);
	printf("%s\n",buffer);
	send(new_socket,hello,strlen(hello),0);
	printf("sent message- hello");

	return 0;
}
