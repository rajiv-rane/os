#include<stdio.h>
#include<stdlib.h>
#define MAX_MEMORY_SIZE 10
#define MAX_PARTITIONS 5
int memory[MAX_MEMORY_SIZE], partitions[MAX_PARTITIONS];
int num_partitions=0;
void initializeMemory() {
	for(int i=0;i<MAX_MEMORY_SIZE;i++) {
		memory[i]=-1;
	}
	for(int i=0;i<MAX_PARTITIONS;i++) {
		partitions[i]=-1;
	}
}
int firstfit(int size) {
	for(int i=0;i<MAX_MEMORY_SIZE;i++) {
		if(memory[i]==-1) {
			int j;
			for(j=i;j<MAX_MEMORY_SIZE && memory[j]==-1;j++) {
				if(j-i+1==size) {
					for(int k=i;k<i+size;k++) {
						memory[k]=size;
					}
					partitions[num_partitions]=i;
					num_partitions++;
					return 0;
				}
			}
			i=j;
		}
	}
	return -1;
}
int bestfit(int size) {
	int bestfitSize=MAX_MEMORY_SIZE;
	int bestfitIndex=-1;
	for(int i=0;i<MAX_MEMORY_SIZE;i++) {
		if(memory[i]==-1) {
			int j;
			int currentsize=0;
			for(j=i;j<MAX_MEMORY_SIZE && memory[j]==-1;j++) {
				currentsize++;
			}
			if(currentsize>=size && (currentsize<bestfitSize || currentsize==MAX_MEMORY_SIZE)) {
				bestfitSize=currentsize;
				bestfitIndex=i;
			}
			i=j;
		}
	}
	if(bestfitIndex!=-1) {
		for(int k=bestfitIndex;k<bestfitIndex+size;k++) {
			memory[k]=size;
		}
		partitions[num_partitions]=bestfitIndex;
		num_partitions++;
		return 0;
	}
	return -1;
}
int worstfit(int size) {
	int worstfitSize=-1;                     //check
	int worstfitIndex=-1;
	for(int i=0;i<MAX_MEMORY_SIZE;i++) {
		if(memory[i]==-1) {
			int j;
			int currentsize=0;
			for(j=i;j<MAX_MEMORY_SIZE && memory[j]==-1;j++) {
				currentsize++;
			}
			if(currentsize>=size && currentsize>worstfitSize) {
				worstfitSize=currentsize;
				worstfitIndex=i;
			}
			i=j;
		}
	}
	if(worstfitIndex!=-1) {
		for(int k=worstfitIndex;k<worstfitIndex+size;k++) {
			memory[k]=size;
		}
		partitions[num_partitions]=worstfitIndex;
		num_partitions++;
		return 0;
	}
	return -1;
}
void deallocatememory(int part) {
	if(memory[partitions[part]]!=-1) {
		int rem=partitions[part]+memory[partitions[part]];
		for(int i=partitions[part];i<rem;i++) {
			memory[i]=-1;
		}
		partitions[part]=-1;
		printf("\nMemory has been deallocate successfully\n");
	}
	else{
		printf("\nMemory has not been deallocate\n");
	}
}
void displaymemory() {
	printf("\nMemory Status\n");
	for(int i=0;i<MAX_MEMORY_SIZE;i++) {
		if(memory[i]==-1)
			printf(".");
		else
			printf("X");
		printf("\n");
	}
}
int main() {
	initializeMemory();
	int choice,size,part,count;
	while(1){
		printf("\nMemory Allocation Technique\n");
		printf("1.FIRST FIT\n2.BEST FIT\n3.WORST FIT\n4.DEALLOCATE MEMORY\n5.DISPLAY MEMORY\n6.EXIT\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		switch(choice) {
			case 1: 
				printf("\nEnter Process Size: ");
				scanf("%d", &size);
				if(firstfit(size)==-1)
					printf("Allocation Failed! Not enough Memory\n");
				else
					printf("Allocation Successfully\n");
				break;
			case 2:
				printf("\nEnter Process Size: ");
				scanf("%d", &size);
				if(bestfit(size)==-1)
					printf("Allocation Failed! Not enough Memory\n");
				else
					printf("Allocation Successfully\n");
				break;	
			case 3:
				printf("\nEnter Process Size: ");
				scanf("%d", &size);
				if(worstfit(size)==-1)
					printf("Allocation Failed! Not enough Memory\n");
				else
					printf("Allocation Successfully\n");
				break;	
			case 4:
				count=0;
				printf("\n");
				for(int i=0;i<MAX_PARTITIONS;i++) {
					if(partitions[i]>=0 && partitions[i]<MAX_MEMORY_SIZE) {
						count++;
						printf("Part %d: Size %d\n",i+1,memory[partitions[i]]);
					}
				}
				printf("Currently there are %d parts to choose from\n",count);
				printf("Enter the part that you want to deallocate: ");
				scanf("%d",&part);
				deallocatememory(part-1);
				break;
			case 5:
				displaymemory();
				break;
			case 6:
				exit(1);
			default:
				printf("Invalid Choice!\n");
		}
	}
	return 0;
}

