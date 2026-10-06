#include <stdio.h>
int main(){
    int at[5],bt[5], priority;

    for(int i = 0;i < 5; i++){
        printf("Enter the Arival time of Process %d\n",i+1);
        scanf("%d",&at[i]);

        printf("Enter the Burst time of Process %d\n",i+1);
        scanf("%d",&bt[i]);
    }

    printf("Enter the priority :\n");
    printf("Enter 1 for Highest first\n");
    printf("Enter 2 for lowest first\n");
    
    scanf("%d",&priority);



    return 0;
}