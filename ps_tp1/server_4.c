/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_4.c
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

// Questions (Partie 2.2)

// L'arrêt est correct avec CTRL-C, kill sur le fils puis sur le père ou l'inverse.
// Lorsqu'on arrête le père en premier, les deux messages de fin sont affichés, alors que lorsqu'on kill le fils,
// seul le message de fin du fils est affiché.
// Afin que le message de fin du père soit également affiché lorsqu'on kill le fils, il faut utiliser sigaction() avec l'argument
// SIGPIPE cette fois-ci.

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

    int pipefd[2];
    pipe(pipefd);

    int fork_id = fork();
    if (fork_id == -1) {
        perror("Erreur de fork");
        exit(EXIT_FAILURE);
    }
    if (fork_id == 0) {
        close(pipefd[1]);
        printf("Du processus fils : %d\n", getpid());
    } else {
        close(pipefd[0]);
        printf("Du processus père : %d\n", getpid());
    }

    printf("Go ! \n");

    while (running) {

        int id = getpid();
        int father_id = getppid();
        int random_nb = rand()%100;

        // Le fils lit dans la pipe and affiche les nombres que le père écrit dans le pipe
        if (fork_id == 0) {
            if (read(pipefd[0], &read_id, sizeof(read_id)) > 0) {
                read(pipefd[0], &read_father_id, sizeof(read_father_id));
                read(pipefd[0], &read_random_nb, sizeof(read_random_nb));
                printf("Read id: %d\n", read_id);
                printf("Read father id: %d\n", read_father_id);
                printf("Read random number: %d\n", read_random_nb);
            } else {
                perror("read");
                break;
            }
        }

        // Le père écrit les nombres dans le pipe
        else {
            write(pipefd[1], &id, sizeof(id));
            write(pipefd[1], &father_id, sizeof(father_id));
            write(pipefd[1], &random_nb, sizeof(random_nb));
            sleep(1);
        }
    }
    close(pipefd[1]);
    close(pipefd[0]);

    printf("After the loop. \n");

    if (fork_id != 0){
        wait(&wstatus);
        printf("Code retour fils : %i. \n", wstatus);
    }
    else {
        printf("END. \n");
    }
    
    return EXIT_SUCCESS;
}
