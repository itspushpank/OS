#include <stdio.h>

int at[5], bt[5], pt[5];

int ct[5], tat[5], rt[5], cat = 0, arival = 0, p = 0, complete = 0;

float sum_tat, sum_wt;

int main()
{

    for (int i = 0; i < 5; i++)
    {
        printf("Enter the Arival Time:   ");
        scanf("%d", &at[i]);
        printf("\nEnter the Burst Time:   ");
        scanf("%d", &bt[i]);
        printf("\nEnter the Priority:   ");
        scanf("%d", &pt[i]);
    }

    int i = 0;
    while (complete < 5)
    {
        for (int i = 0; i < 5; i++)
        {
            if (at[i] <= arival && pt[i] < p )
            {
                ct[i]= bt[i] 
            }
        }
        i++;
    }
}