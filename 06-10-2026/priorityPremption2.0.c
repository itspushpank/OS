#include <stdio.h>
#include <limits.h>

#define MAX_PROCESSES 100

void sortByArrivalTime(int n, int pid[], int at[], int bt[], int priority[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                int temp;
                temp = at[j]; at[j] = at[j + 1]; at[j + 1] = temp;
                temp = bt[j]; bt[j] = bt[j + 1]; bt[j + 1] = temp;
                temp = priority[j]; priority[j] = priority[j + 1]; priority[j + 1] = temp;
                temp = pid[j]; pid[j] = pid[j + 1]; pid[j + 1] = temp;
            }
        }
    }
}

void preemptivePriorityScheduling(int n, int pid[], int at[], int bt[], int priority[]) {
    int remaining_bt[MAX_PROCESSES];
    int wt[MAX_PROCESSES] = {0};
    int tat[MAX_PROCESSES] = {0};
    int ct[MAX_PROCESSES] = {0};
    int completed = 0;
    int current_time = 0;
    int min_priority_idx;
    int found;

    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
    }

    printf("\nGantt Chart:\n");
    printf("|");

    while (completed < n) {
        min_priority_idx = -1;
        found = 0;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && remaining_bt[i] > 0) {
                if (!found || priority[i] < priority[min_priority_idx]) {
                    min_priority_idx = i;
                    found = 1;
                }
            }
        }

        if (!found) {
            current_time++;
            continue;
        }

        printf(" P%d |", pid[min_priority_idx]);
        remaining_bt[min_priority_idx]--;
        current_time++;

        if (remaining_bt[min_priority_idx] == 0) {
            completed++;
            ct[min_priority_idx] = current_time;
            tat[min_priority_idx] = ct[min_priority_idx] - at[min_priority_idx];
            wt[min_priority_idx] = tat[min_priority_idx] - bt[min_priority_idx];
        }
    }

    printf("\n\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", pid[i], at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);
}

int main() {
    int n;
    int pid[MAX_PROCESSES];
    int at[MAX_PROCESSES];
    int bt[MAX_PROCESSES];
    int priority[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess P%d:\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &priority[i]);
    }

    sortByArrivalTime(n, pid, at, bt, priority);

    preemptivePriorityScheduling(n, pid, at, bt, priority);

    return 0;
}