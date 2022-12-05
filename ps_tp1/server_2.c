/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_2.c
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

int running = 1;

void stop_handler(int sig)
{
    printf("\n SIGNAL : %i \n", sig); 
    running = 0;
}

/// Questions (Partie 1.2)

// Le message de stop_handler() est affiché lorsqu'on utilise CRTL-C dans le Term1.
// Il n'est pas affiché si on utilise kill sans l'option -s INT.
// Il est affiché si on utilise cette option ("équivalent" à un CTRL-C).
// Afin que le message de stop_handler() soit toujours affiché, on utilise sigaction()
// en remplaçant cette fois SIGINT par SIGTERM dans l'argument de sigaction().

// En utilisant la commande kill -s KILL, le message de stop_handler() n'apparaît plus.
// Sans l'option -s KILL, le message apparaît bien.
// On ne peut pas faire apparaître le message avec l'option -s KILL car sigaction() ne reçoit
// pas SIGKILL en argument.
// Si on donne en argument à la commande kill le numéro du processus père, on obtient :
// - sans l'option -s KILL : aucun effet, l'exécution se poursuit.
// - avec l'option -s KILL : le terminal Term1 se ferme.

// Si on ne modifie pas la variable running, le programme ne s'arrête plus, que l'on utilise un
// CTRL-C, un kill ou un kill -9.

// Questions (Partie 1.2)

// Le message de exit_message() apparaît pour CTRL-C et pour kill, mais pas pour kill -9.

void exit_message(void)
{
    printf("Message de fin. \n");
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = stop_handler; sigemptyset(&sa.sa_mask); sa.sa_flags = 0;

    // Traitement des erreurs
    if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL)){
        perror("Erreur sigaction \n");
        exit(EXIT_FAILURE);
    }

    if (atexit(exit_message) != 0) {
        fprintf(stderr, "cannot set exit function \n");
        exit(EXIT_FAILURE);
    }

    printf("Go ! \n");

    while (running){
        int id = getpid();
        int father_id = getppid();
        printf("id %d father_id %d \n", id, father_id);

        int random_nb = rand()%100;
        printf("random (0-99) : %d \n", random_nb);

        sleep(1);
    }

    printf("After the loop. \n");
    
    return EXIT_SUCCESS;
}
