#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void calculateTimes(struct Process *processes, int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    
    processes[0].waiting_time = 0;
    processes[0].turnaround_time = processes[0].burst_time;
    
    for (int i = 1; i < n; ++i) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
    
    for (int i = 0; i < n; ++i) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; ++i) {
        printf("Process %d:\n", i + 1);
        processes[i].id = i + 1;
        processes[i].arrival_time = 0;
        printf("Arrival Time: %d\n", processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("\n");
    }
    
    calculateTimes(processes, n);
    
    return 0;
}
