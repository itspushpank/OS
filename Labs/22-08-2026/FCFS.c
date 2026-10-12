#include <stdio.h>
int main()
{
    int p;
    printf("Enter the number of process : ");
    scanf("%d", &p);
    printf("\n");

    int AT[p],BT[p],CT[p],TAT[p],WT[p];

    printf("Enter the arival & burst time of proesses :\n");
    for(int i=0;i<p;i++)
    {
        printf("Arival time of process %d :",i+1);
        scanf("%d",&AT[i]);

        printf("Burst time of process %d :",i+1);
        scanf("%d",&BT[i]);
        printf("\n");
    }

    int current_time = 0;
    
    for(int i=0;i<p;i++)
    {
        if(current_time < AT[i])
            current_time = AT[i];
        
        current_time += BT[i];
        CT[i] = current_time;

        TAT[i]= CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }

    float Total_TAT = 0, Total_WT = 0;

    printf("\nP_id\t AT \t BT \t CT \t TAT \t WT");

    for (int i = 0; i < p; i++)
    {
        printf("\n %d  \t %d \t %d \t %d \t %d \t %d",i+1,AT[i],BT[i],CT[i],TAT[i],WT[i]);

        Total_TAT += TAT[i];
        Total_WT += WT[i];

    }
    printf("\n");

    printf("\nAverage TAT : %f",Total_TAT / p);
    printf("\nAverage WT : %f",Total_WT / p);

    
    return 0;
}