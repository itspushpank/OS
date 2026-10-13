#include <stdio.h>
#include <stdlib.h>

typedef struct Process{
    int pid;
    int at;    
    int bt;    
    int remBT; 
    int ct;    
    int tat;   
    int wt;    
    int done;  
}Process;
#define MAX_SIZE 5

typedef struct {
    Process items[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

CircularQueue* createCircularQueue() {
    CircularQueue* q = (CircularQueue*)malloc(sizeof(CircularQueue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(CircularQueue* q) {
    return q->front == -1;
}

int isFull(CircularQueue* q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

void enqueue(CircularQueue* q, Process value) {
    if (isFull(q)) {
        printf("Circular Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->items[q->rear] = value;
    printf("Enqueued: %d\n", value);
}

Process dequeue(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Circular Queue is empty\n");
        return ;
    }
    Process value = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    return value;
}

Process peek(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Circular Queue is empty\n");
        return ;
    }
    return q->items[q->front];
}

void display(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Circular Queue is empty\n");
        return;
    }
    printf("Circular Queue: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear) break;
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}


int main() {
    CircularQueue* q = createCircularQueue();
    
    int n, i, completed = 0;
    Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);


    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].done = 0;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remBT = p[i].bt;   
    }


    int currentTime = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int idx = -1;

        for (i = 0; i < n; i++) {
            if (p[i].at <= currentTime && !p[i].done) {

                enqueue(q,p[i]);

                idx = i;
            }
        }


        if (q->front == q->rear) {
            int nextAT = 999999;
            for (i = 0; i < n; i++) {
                if (!p[i].done && p[i].at < nextAT)
                    nextAT = p[i].at;
            }
            currentTime = nextAT;
            continue;
        }


        p[idx].remBT--;
        currentTime++;
        
        if (p[idx].remBT == 0) {
            p[idx].done = 1;
            p[idx].ct  = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt  = p[idx].tat - p[idx].bt;

            totalTAT += p[idx].tat;
            totalWT  += p[idx].wt;
            completed++;
        }
    }


    printf("\n--- SRTF (Preemptive SJF) Result ---\n");
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
