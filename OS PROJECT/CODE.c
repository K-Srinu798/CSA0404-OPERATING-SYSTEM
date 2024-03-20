#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define MAX_MEMORY_BLOCKS 10

typedef struct {
    int id;
    int size;
    int allocated;
} Process;

typedef struct {
    int id;
    int size;
    int allocated;
} MemoryBlock;

Process processes[MAX_PROCESSES];
MemoryBlock memory[MAX_MEMORY_BLOCKS];

int numProcesses = 0;
int numMemoryBlocks = 0;

void firstFit() {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numMemoryBlocks; j++) {
            if (!memory[j].allocated && memory[j].size >= processes[i].size) {
                memory[j].allocated = 1;
                printf("Process %d allocated to memory block %d using First Fit.\n", processes[i].id, memory[j].id);
                break;
            }
        }
    }
}

void bestFit() {
    for (int i = 0; i < numProcesses; i++) {
        int bestFitIdx = -1;
        for (int j = 0; j < numMemoryBlocks; j++) {
            if (!memory[j].allocated && memory[j].size >= processes[i].size) {
                if (bestFitIdx == -1 || memory[j].size < memory[bestFitIdx].size) {
                    bestFitIdx = j;
                }
            }
        }
        if (bestFitIdx != -1) {
            memory[bestFitIdx].allocated = 1;
            printf("Process %d allocated to memory block %d using Best Fit.\n", processes[i].id, memory[bestFitIdx].id);
        }
    }
}

void worstFit() {
    for (int i = 0; i < numProcesses; i++) {
        int worstFitIdx = -1;
        for (int j = 0; j < numMemoryBlocks; j++) {
            if (!memory[j].allocated && memory[j].size >= processes[i].size) {
                if (worstFitIdx == -1 || memory[j].size > memory[worstFitIdx].size) {
                    worstFitIdx = j;
                }
            }
        }
        if (worstFitIdx != -1) {
            memory[worstFitIdx].allocated = 1;
            printf("Process %d allocated to memory block %d using Worst Fit.\n", processes[i].id, memory[worstFitIdx].id);
        }
    }
}

int main() {
    int choice;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numMemoryBlocks);
    printf("Enter details of memory blocks (id size):\n");
    for (int i = 0; i < numMemoryBlocks; i++) {
        scanf("%d %d", &memory[i].id, &memory[i].size);
    }
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter details of processes (id size):\n");
    for (int i = 0; i < numProcesses; i++) {
        scanf("%d %d", &processes[i].id, &processes[i].size);
    }
    printf("Choose memory allocation strategy:\n");
    printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            firstFit();
            break;
        case 2:
            bestFit();
            break;
        case 3:
            worstFit();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    return 0;
}
