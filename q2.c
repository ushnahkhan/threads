#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<stdlib.h>
int**A;
int**B;
int**C;
int erow=0;
int srow=0;
int n=0;
void*productthread(void*paras)
{
	for(int i=srow;i<erow;i++)
	{
		for(int j=0;j<n;j++)
		{
			C[i][j]=0;
			for(int k=0;k<n;k++)
			{
				C[i][j]=C[i][j]+(A[i][k]*B[k][j]);
			}
			
		}
	}
	pthread_exit(NULL);
}
int main(int num,char*args[])
{
	n=atoi(args[1]);
	if(n<128)
	{
		printf("Invalid value of n!\n");
		return 1;
	}
	A=(int**)malloc(n*sizeof(int*));
	B=(int**)malloc(n*sizeof(int*));
	C=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
	{
		A[i]=(int*)malloc(n*sizeof(int));
		B[i]=(int*)malloc(n*sizeof(int));
		C[i]=(int*)malloc(n*sizeof(int));
	}
	srand(time(NULL));
	FILE*afile=fopen("A.txt","w");
	FILE*bfile=fopen("B.txt","w");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			A[i][j]=rand()%100;
			fprintf(afile,"%d ",A[i][j]);
			B[i][j]=rand()%100;
			fprintf(bfile,"%d ",B[i][j]);
		}
		fprintf(afile,"\n");
		fprintf(bfile,"\n");
	}
	fclose(afile);
	fclose(bfile);
	printf("[");
	int**info=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
	{
		info[i]=(int*)malloc(3*sizeof(int));
	}
	for(int i=1;i<=n;i++)
	{
		srow=erow=0;
		time_t start=time(NULL);
		pthread_t *threadid=(pthread_t*)malloc(i*sizeof(pthread_t));
		for(int j=0;j<i;j++)
		{
			srow=j*(n/i);
			erow=srow+(n/i);
			pthread_create(&threadid[j],NULL,productthread,NULL);
		}
		for(int j=0;j<i;j++)
			pthread_join(threadid[j],NULL);	
		time_t end=time(NULL);
		int duration=end-start;
		info[i-1][0]=n;
		info[i-1][1]=i;
		info[i-1][2]=duration;
		printf("(%d,%d,%d), ",n,i,duration);	
	}
	printf("]\n");
	FILE*cfile=fopen("C.txt","w");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			fprintf(cfile,"%d ",C[i][j]);
		}
		fprintf(cfile,"\n");
	}
	fclose(cfile);
	return 0;
}

