#include <stdio.h>

#define MAX 100

struct Process {
    int pid;
    int at;
    int bt;
    int priority;
    int ct;
    int tat;
    int wt;
    int rt;
    int completed;
};

void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void priorityScheduling(struct Process p[], int n) {
    int completed = 0;
    int currentTime = 0;
    int minPriority;
    int shortestIdx;

    while (completed < n) {
        minPriority = 9999;
        shortestIdx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !p[i].completed) {
                if (p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    shortestIdx = i;
                } else if (p[i].priority == minPriority) {
                    if (p[i].at < p[shortestIdx].at) {
                        shortestIdx = i;
                    }
                }
            }
        }

        if (shortestIdx == -1) {
            currentTime++;
            continue;
        }

        if (p[shortestIdx].rt == p[shortestIdx].bt) {
            p[shortestIdx].rt = currentTime;
        }

        p[shortestIdx].bt--;
        currentTime++;

        if (p[shortestIdx].bt == 0) {
            p[shortestIdx].ct = currentTime;
            p[shortestIdx].tat = p[shortestIdx].ct - p[shortestIdx].at;
            p[shortestIdx].wt = p[shortestIdx].tat - (p[shortestIdx].ct - p[shortestIdx].rt);
            p[shortestIdx].completed = 1;
            completed++;
        }
    }
}

void printResults(struct Process p[], int n) {
    float totalWT = 0, totalTAT = 0;

    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt + p[i].wt + p[i].tat - p[i].ct + p[i].at,
               p[i].priority, p[i].ct, p[i].tat, p[i].wt);
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
}

int main() {
    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &p[i].priority);
        p[i].completed = 0;
        p[i].rt = -1;
    }

    sortByArrival(p, n);
    priorityScheduling(p, n);
    printResults(p, n);

    return 0;
}