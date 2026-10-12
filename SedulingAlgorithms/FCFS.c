#include <stdio.h>

struct Process
{
    int pid;
    int at;  
    int bt;  
    int ct;  
    int tat; 
    int wt;  
};

int main()
{
    int n, i, j;
    struct Process p[20], temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);


    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }


    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }


    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    for (i = 0; i < n; i++)
    {
        if (currentTime < p[i].at)
            currentTime = p[i].at; 

        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        currentTime = p[i].ct;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }


    printf("\n--- FCFS Scheduling Result ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                p[i].pid, p[i].at, p[i].bt,
                p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nAverage Waiting Time    = %.2f\n", totalWT / n);

    return 0;
}