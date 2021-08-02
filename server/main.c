#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "fibonacci.h"

int main(int argc, char *argv[]){
    
   
    //Criando e testando a criação de um socket.
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1){
        printf("Não foi possivel criar o socket.\n");
        return -1;
    }

    //Configurando a struct do socket do servidor
    struct sockaddr_in servidor;
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_port = htons(1234);

    //Linkando o socket e suas configurações.
    if(bind(socket_desc, (struct sockaddr *)&servidor, sizeof(servidor)) < 0){
        printf("Erro ao fazer link\n");
    }
    printf("Link realizado com sucesso\n");
    listen(socket_desc, 5);

    //Aceitando e tratando novas conexões.
    struct sockaddr_in cliente;
    printf("Aguardando por conexões ...\n");
    int c = sizeof(cliente);
    int connection = accept(socket_desc, (struct sockaddr *)&cliente, (socklen_t *)&c);
    if (connection < 0){
        printf("Erro ao receber conexão\n");
        return -1;
    }
    
    //Pegando IP e porta do cliente.
    struct sockaddr_in client;
    char *client_ip;
    int client_port;
    client_ip = inet_ntoa(client.sin_addr);
    client_port = ntohs(client.sin_port);
    printf("Cliente conectado: %s : [%d]\n", client_ip, client_port);

    
    //Enviando mensagem ao cliente. 
    char *message;
    message = "Digite o termo de fibonacci desejado: ";
    write(connection, message, strlen(message));


    //Lendo os dados.
    int tamanho;
    int n_esimo;
    if ((tamanho = read(connection, (int *)&n_esimo, sizeof(n_esimo))) < 0){
        printf("Erro ao receber dados do client.\n");
        return -1;
    }
    printf("Termo recebido: %d\n", n_esimo);

   
    //Calculo do fibonacci.
    unsigned long long  answer[n_esimo];
    answer[0] = 0;
    answer[1] = 1;

    for (int i = 2; i < n_esimo; i++){
        answer[i] = -1;
    }
    recursiveFibonacci(answer, n_esimo-1);

    write(connection, answer, sizeof(answer));
    close(connection);

    
    return 0;
}
