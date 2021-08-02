#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


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
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
    servidor.sin_port = htons(1234);

    //Conectando no servidor
    if (connect(socket_desc, (struct sockaddr *)& servidor, sizeof(servidor)) < 0){
        printf("Não foi possivel a conexão\n");
        return -1;
    }
    printf("Conectado no servidor.\n");

    //Troca de Mensagens
    int tamanho;
    char msg_server[1024];
    if ((tamanho = recv(socket_desc, msg_server, 1024, 0 )) < 0){
        printf("Falha ao receber mensagem do servidor.\n");
        return -1;
    }
    msg_server[tamanho] = '\0';
    printf(" %s\n", msg_server);

    int n_esimo;
    scanf("%i", &n_esimo);
    if(send(socket_desc, (int *)&n_esimo, sizeof(n_esimo), 0) < 0){
        printf("Falha ao enviar o n-esimo termo\n");
        return -1;
    }
    printf("Termo enviado\n");


    unsigned long long termos_fibonnaci[n_esimo];
    if ((tamanho = recv(socket_desc, termos_fibonnaci, sizeof(termos_fibonnaci), 0 )) < 0){
        printf("Falha ao receber os termos do servidor.\n");
        return -1;
    }
    printf("Termos recebidos\n");

    for (int i = 0; i < n_esimo; i++){
        printf("%d : %llu \n", i+1, termos_fibonnaci[i]);
    }
        
    return 0;
}
