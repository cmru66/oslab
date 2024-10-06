#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SEGSIZE 100

int main(int argc, char *argv[]) {
    int shmid;
    key_t key;
    char *segptr;
    char buff[] = "poooda..... ";

    // Create a unique key for the shared memory segment
    key = ftok(".", 's');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Try to create a new shared memory segment
    shmid = shmget(key, SEGSIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid == -1) {
        // If creation fails, try to access an existing segment
        if ((shmid = shmget(key, SEGSIZE, 0)) == -1) {
            perror("shmget");
            exit(1);
        }
    } else {
        printf("Creating a new shared memory segment...\n");
        printf("SHMID: %d\n", shmid);
    }

    // Display current shared memory segments
    system("ipcs -m");

    // Attach to the shared memory segment
    segptr = (char *)shmat(shmid, NULL, 0);
    if (segptr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Write data to shared memory
    printf("Writing data to shared memory...\n");
    strcpy(segptr, buff);
    printf("DONE\n");

    // Read data from shared memory
    printf("Reading data from shared memory...\n");
    printf("DATA: %s\n", segptr);
    printf("DONE\n");

    // Detach from shared memory
    if (shmdt(segptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Remove the shared memory segment
    printf("Removing shared memory segment...\n");
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        printf("Can't remove shared memory segment...\n");
    } else {
        printf("Removed successfully\n");
    }

    return 0;
}
