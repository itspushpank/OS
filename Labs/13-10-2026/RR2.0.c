#include <stdio.h>

int queue[100];
int front = -1;
int rear = -1;
int size = 100;

void enqueue(int val){
    if(rear == size -1){
        return;
    }
    else {
        if(front == -1){
            front =0;
        }
        queue[++rear] = val;
    }
} 

int dequeue(){
    if(front == -1 || front > rear){
        return -1;
    }
    else{
        return queue[front++];
    }

}


int main(){
    int n,tq;
    printf("Enter the no. of process: ");
    scanf("%d",&n);
    
    int at[n],bt[n],ct[n],tat[n],rt[n],found[n],wt[n];

    for(int i=0;i<n;i++){
        printf("Enter the arrival time of P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Enter the burst time of P%d: ",i+1);
        scanf("%d",&bt[i]);

        rt[i] = bt[i];
        found[i] = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d",&tq);

    int completed =0;
    int curr_time =0;

    while(completed < n){
        for (int i=0;i<n;i++){
            if(at[i]<=curr_time && found[i]== 0 ){
                enqueue(i);
                found[i] = 1;
            }
        }
        

        if(front == -1 || front >rear){
            curr_time++;
            continue;
        }
        int x = dequeue();
        
        if(rt[x]>tq){
            rt[x] = rt[x] -tq;
            curr_time = curr_time + tq;
        }else{
            curr_time= curr_time + rt[x];
            rt[x] =0;
        }

        

        for (int i=0;i<n;i++){
            if(at[i]<=curr_time && found[i]== 0 ){
                enqueue(i);
                found[i] = 1;
            }
        }
        
        if (rt[x] > 0) {
            enqueue(x);
        }

        if(rt[x] == 0){
            ct[x] = curr_time;
            completed++;
            tat[x] = ct[x] - at[x];
            wt[x] = tat[x] - bt[x];

        }

    }


    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    float avgWT = 0, avgTAT = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
                i + 1, at[i], bt[i],
                ct[i], tat[i], wt[i]);

        avgWT += wt[i];
        avgTAT += tat[i];
    }
    
    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);


    return 0;
}