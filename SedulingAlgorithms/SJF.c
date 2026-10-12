#include <stdio.h>

struct Process {
    int pid;
    int at;   
    int bt;   
    int ct;   
    int tat;  
    int wt;   
    int done; 
};

int main() {
    int n, i, completed = 0;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].done = 0;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    
    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = 999999;

        
        for (i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !p[i].done) {
                if (p[i].bt < minBT) {
                    minBT = p[i].bt;
                    idx = i;
                }
                else if (p[i].bt == minBT && idx != -1) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        
        if (idx == -1) {
            int nextAT = 999999;
            for (i = 0; i < n; i++) {
                if (!p[i].done && p[i].at < nextAT)
                    nextAT = p[i].at;
            }
            currentTime = nextAT;
            continue;
        }

        
        p[idx].ct  = currentTime + p[idx].bt;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
        p[idx].done = 1;

        currentTime = p[idx].ct;
        completed++;

        totalTAT += p[idx].tat;
        totalWT  += p[idx].wt;
    }

    
    printf("\n--- SJF Scheduling Result ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                p[i].pid, p[i].at, p[i].bt,
                p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nAverage Waiting Time    = %.2f\n", totalWT / n);

    return 0;
}