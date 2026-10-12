#include<stdio.h>
int main() {
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
    if (current_time < AT[i])
    current_time = AT[i];

    int temp = 0;

    for(int i = 0; i<p ; i++){
        if(AT[i]== current_time){
            temp=BT[i]
            if (BT[i])
            {
                /* code */
            }
        }
            
    }

    return 0;
}