#include<stdio.h>
int main()
{
	int i,j,n,a[50],frame[10],no,k,avail,count=0;
	printf("\nEnter the number of pages: ");
	scanf("%d",&n);
	
	printf("\nEnter the reference string: ");
	for(i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	
	printf("\nEnter the number of frames: ");
	scanf("%d",&no);

	for (i=0;i<no;i++)
	{
		frame[i]=-1;
	}
	j=0;
	
	printf("\n\nReference string\t\tPage frames\n\n");
	for(i=1;i<=n;i++)
	{
		printf("%d\t\t",a[i]);
		avail=0;
		
		for(k=0;k<no;k++)
		{
			if(frame[k]==a[i])
			{
				avail=1;
			}
		}
		if(avail==0)
		{
			frame[j]=a[i];
			j=(j+1)%no;
			count++;
			
			for(k=0;k<no;k++)
			{
				printf("\t\t%d\t",frame[k]);
			}
		}
		printf("\n");
	}
	printf("\nNumber of page faults got using FIFO Page Replacement Algorithm is %d",count);
}
	
