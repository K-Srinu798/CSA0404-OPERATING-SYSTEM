#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

#define SHMSZ 1024  // Size of the shared memory segment

int main() {
    int shmid;
    key_t key;
    char *shm, *s;
    const char *message = "Hello, shared memory!";

    // Generate a key for the shared memory segment
    if ((key = ftok(".", 'R')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the shared memory segment
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the address space of the process
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Writer process
    if (fork() == 0) {
        // Write to the shared memory segment
        strcpy(shm, message);
        exit(0);
    }
    // Reader process
    else {
        // Wait for the writer process to complete
        wait(NULL);

        // Read from the shared memory segment
        for (s = shm; *s != '\0'; s++)
            putchar(*s);
        putchar('\n');

        // Detach the shared memory segment from the address space of the process
        if (shmdt(shm) == -1) {
            perror("shmdt");
            exit(1);
        }

        // Delete the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    }

    return 0;
}
