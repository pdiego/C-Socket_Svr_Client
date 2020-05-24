// Servidor C/C++ para escuchar por un puerto. Programacion con sockets.
// fuente: https://www.geeksforgeeks.org/socket-programming-cc/
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8181

using namespace std;


int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0};
	// Por ahora estoy evitando un warning pero este texto debería cambiar.
    const char *hello = "has llegado al server!! ";
	const char *strFinal = "Q";
       
    // Creamos el socket con 
	// 	AF_INET -> IPv4 
	//	SOCK_STREAM -> Funciona sobre TCP y tiene control de errores para recibir lo que se ha enviado. <> UDP para streaming.
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Establecemos las variables del SOCKET. 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forzamos el puerto 8181 y asignamos opciones establecidas.
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
	// marcamos el socket como escuchador, pasivo.
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
	// esto es lo que acepta la conexión del socket que hemos cnfigurado.
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
	
	while( strcmp(strFinal, buffer) > 0 || strcmp(strFinal, buffer) < 0 ) {
		valread = read( new_socket , buffer, 1024); 
		printf("%s\n",buffer ); 
		send(new_socket , hello , strlen(hello) , 0 ); 
		printf("Enviada verificación\n"); 
	}

	printf("Fin del proceso... \n"); 
    return 0; 
} 
