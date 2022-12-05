/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_5.c
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
    fd = open(myfifo, O_WRONLY); // avant la boucle

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
        int id = getpid();
        int father_id = getppid();
        int random_nb = rand()%100;

        write(fd, &id, sizeof(id));
        write(fd, &father_id, sizeof(father_id));
        write(fd, &random_nb, sizeof(random_nb));
        sleep(1);
    }
    close(fd);

    printf("After the loop. \n");

    if (wait(&wstatus) == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(wstatus)) {
        printf("Code retour fils : %d. \n", WEXITSTATUS(wstatus));
    }

    printf("END. \n");

    return EXIT_SUCCESS;
}
