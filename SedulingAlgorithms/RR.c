#include <stdio.h>

#define MAX 20

struct Process {
    int pid;
    int at;
    int bt;
    int remBT;
    int ct;
    int tat;
    int wt;
    int inQueue;
};

struct Queue {
    int items[MAX];
    int front;
    int rear;
    int count;
};

void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isEmpty(struct Queue *q) {
    return q->count == 0;
}

int isFull(struct Queue *q) {
    return q->count == MAX;
}

void enqueue(struct Queue *q, int value) {
    if (!isFull(q)) {
        q->rear = (q->rear + 1) % MAX;
        q->items[q->rear] = value;
        q->count++;
    }
}

int dequeue(struct Queue *q) {
    int value = -1;
    if (!isEmpty(q)) {
        value = q->items[q->front];
        q->front = (q->front + 1) % MAX;
        q->count--;
    }
    return value;
}

int main() {
    int n, i, quantum, completed = 0;
    struct Process p[MAX];
    struct Queue readyQueue;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].inQueue = 0;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remBT = p[i].bt;
    }

    initQueue(&readyQueue);
    
    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;
    
    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !p[i].inQueue && p[i].remBT > 0) {
                enqueue(&readyQueue, i);
                p[i].inQueue = 1;
            }
        }
        
        if (isEmpty(&readyQueue)) {
            int nextAT = 999999;
            for (i = 0; i < n; i++) {
                if (p[i].remBT > 0 && p[i].at < nextAT) {
                    nextAT = p[i].at;
                }
            }
            currentTime = nextAT;
            continue;
        }
        
        int idx = dequeue(&readyQueue);
        p[idx].inQueue = 0;
        
        int execTime = (p[idx].remBT > quantum) ? quantum : p[idx].remBT;
        p[idx].remBT -= execTime;
        currentTime += execTime;
        
        for (i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !p[i].inQueue && p[i].remBT > 0 && i != idx) {
                enqueue(&readyQueue, i);
                p[i].inQueue = 1;
            }
        }
        
        if (p[idx].remBT > 0) {
            enqueue(&readyQueue, idx);
            p[idx].inQueue = 1;
        } else {
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            totalTAT += p[idx].tat;
            totalWT += p[idx].wt;
            completed++;
        }
    }

    printf("\n--- Round Robin Scheduling Result (Quantum = %d) ---\n", quantum);
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