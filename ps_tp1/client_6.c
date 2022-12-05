/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_6.c
 */

// for printf()
#include <stdio.h>
// For rand(), srand(), sleep(), EXIT_SUCCESS
#include <stdlib.h>
// For time()
#include <time.h>
// For getpid(), getppid()
#include <unistd.h>
// For sigaction()
#include <signal.h>
// For wait()
#include <sys/wait.h>
// For open(), O_WRONLY
#include <sys/stat.h> 
#include <fcntl.h>
#include <sys/types.h>
// For inet_addr()
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
// For bzero()
#include <strings.h>
#include <sys/socket.h>
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define MAX 80
#define LISTEN_BACKLOG 50
#define PORT 8080
#define SA struct sockaddr

int running = 1;

void stop_handler(int sig)
{
    printf("\n SIGNAL : %i \n", sig); 
    running = 0;
}

void exit_message(void)
{
    printf("Message de fin. \n");
}

int main()
{
    int read_id;
    int read_father_id;
    int read_random_nb;

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    socklen_t peer_addr_size;
 
    // Création du socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("La création du socket a échoué.\n");
        exit(0);
    }
    else {
        printf("Le socket a été créé avec succès.\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    // On assigne IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Adresse de loopback
    servaddr.sin_port = htons(PORT);
    // Connexion du socket client au socket serveur (sur l'adresse de loopback)
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))) { 
        perror("La connexion au serveur a échoué.\n");
        return EXIT_FAILURE;
    } else {
        printf("Connexion au serveur établie.\n");
    }

    struct sigaction sa;
    sa.sa_handler = stop_handler; sigemptyset(&sa.sa_mask); sa.sa_flags = 0;

    // sigaction
    if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) || sigaction(SIGPIPE, &sa, NULL)){
        perror("Erreur sigaction \n");
        exit(EXIT_FAILURE);
    }

    // atexit
    if (atexit(exit_message) != 0) {
        perror("cannot set exit function \n");
        exit(EXIT_FAILURE);
    }

    printf("Go ! \n");

    while (running) {
        if (read(sockfd, &read_id, sizeof(read_id)) > 0) {  // Le client reçoit les nombres générés par le serveur avec read()
            read(sockfd, &read_father_id, sizeof(read_father_id));
            read(sockfd, &read_random_nb, sizeof(read_random_nb));
            printf("Read id: %d\n", read_id);
            printf("Read father id: %d\n", read_father_id);
            printf("Read random number: %d\n", read_random_nb);
        }
        else {
            perror("read");
            break;
        }
    }

    printf("END. \n");
    
    return EXIT_SUCCESS;
}