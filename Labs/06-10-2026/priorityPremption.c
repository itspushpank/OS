#include <stdio.h>

int at[5], bt[5], pt[5];

int ct[5], tat[5], rt[5], cat = 0, arival = 0, idx, f, complete = 0;

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

    for (int i = 0; i < 5; i++)
    {
        rt[i] = bt[i];
    }

    while (complete < 5)
    {
        idx = -1;
        f = 0;
        for (int i = 0; i < 5; i++)
        {
            if (at[i] <= arival && rt[i] > 0)
            {
                if (!f || pt[i] < pt[idx])
                {
                    idx = i;
                    f = 1;
                }
            }

            if(!f){
                cat++;
                continue;
            }

            
        }
    }
}