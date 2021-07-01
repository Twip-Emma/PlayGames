#include<stdio.h>
int main()
{
    int i,j,n;
    int count=0;

    
    scanf("%d",&n);
    int a[n];
    for(int i=0;i<n;i++)
    {
 	   scanf("%d",&a[i]);
	}
	
    printf("0");
    
    for(i=1;i<n;i++)
	{
        count=0;
        for(j=0;j<i;j++)
		{
            if(a[i]>a[j])
            count++;
        }
        printf(" %d",count);
    }
    return 0;
}
