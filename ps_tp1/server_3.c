/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmation système - TP n°1
 *
 * server_3.c
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

int running = 1;

void stop_handler(int sig)
{
    printf("\n SIGNAL : %i \n", sig); 
    running = 0;
}

// Questions (Partie 2.1)

// On peut distinguer les messages du père de ceux du fils grâce aux identifiants des processus fils, qui sont différents. (Remarque : on a par
// contre l'égalité entre le "father processus id" (obtenu via getppid()) du fils et le "processus id" (obtenu via getpid()) du père.)
// Les deux processus s'arrêtent avec un CTRL-C.

// Lorsqu'on utilise la commande ps a, on remarque qu'il y a deux processus ./server_3 qui tournent (dû au fork() utilisé dans 
// le programme).
// Après avoir kill le fils, il change d'état mais reste visible (on le voit grâce à la commande ps a, où il apparaît <defunct>).
// Après avoir kill le père, le fils continue mais perd le lien de parenté (le "father processus id" devient par défaut 1) et le fils n'apparaît plus
// dans la liste des processus (via la commande ps a).

// Après avoir tué le processus père, lorsqu'on tue le processus fils avec CTRL-C ou kill, le code de retour du fils vaut 0 dans les deux cas, mais
// il vaut 9 lorsqu'on le tue avec kill -9.

void exit_message(void)
{
    printf("Message de fin. \n");
}

int main()
{
    int fork_id = fork();
    int wstatus;

    struct sigaction sa;
    sa.sa_handler = stop_handler; sigemptyset(&sa.sa_mask); sa.sa_flags = 0;

    // Traitement des erreurs
    if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL)){
        perror("Erreur sigaction \n");
        exit(EXIT_FAILURE);
    }

    if (atexit(exit_message) != 0) {
        perror("cannot set exit function \n");
        exit(EXIT_FAILURE);
    }

    printf("Go ! \n");

    while (running){
        if (fork_id == 0){
        printf("FILS : ");
        }
        else if (fork_id != 0){
        printf("PÈRE : ");
        }

        int id = getpid();
        int father_id = getppid();
        printf("id %d father_id %d \n", id, father_id);

        int random_nb = rand()%100;
        printf("random (0-99) : %d \n", random_nb);

        sleep(1);
    }

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
