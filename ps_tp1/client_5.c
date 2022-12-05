/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * client_5.c
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
// For open(), O_RDONLY
#include <sys/stat.h> 
#include <fcntl.h>

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
    int wstatus;

    int fd;

    // FIFO
    char * myfifo = "./monfifo";

    int read_id;
    int read_father_id;
    int read_random_nb;

    struct sigaction sa;
    sa.sa_handler = stop_handler; sigemptyset(&sa.sa_mask); sa.sa_flags = 0;

    // Traitement des erreurs
    if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) || sigaction(SIGPIPE, &sa, NULL)){
        perror("Erreur sigaction \n");
        exit(EXIT_FAILURE);
    }

    if (atexit(exit_message) != 0) {
        perror("cannot set exit function \n");
        exit(EXIT_FAILURE);
    }

    printf("Go ! \n");

    while (running) {
        // Open FIFO for Read only
        fd = open(myfifo, O_RDONLY);

        if (read(fd, &read_id, sizeof(read_id)) > 0) {
            read(fd, &read_father_id, sizeof(read_father_id));
            read(fd, &read_random_nb, sizeof(read_random_nb));
            printf("Read id: %d\n", read_id);
            printf("Read father id: %d\n", read_father_id);
            printf("Read random number: %d\n", read_random_nb);
        }
        else {
            perror("read");
            break;
        }
        close(fd);
    }

    printf("END. \n");
    
    return EXIT_SUCCESS;
}
