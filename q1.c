#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>
#include<sys/types.h>

#define size 50000
 void quicksort(int data[],int l,int h)
 {
 	if(l<h)
 	{
 		int piv=data[h];
 		int i=l-1;
 		for(int j=l;j<h;j++)
 		{
 			if(data[j]<piv)
 			{
 				i++;
 				int temp=data[i];
 				data[i]=data[j];
 				data[j]=temp;
 			}
 		}
 		int temp=data[i+1];
 		data[i+1]=data[h];
 		data[h]=temp;
 		piv=i+1;
 		quicksort(data,l,piv-1);
 		quicksort(data,piv+1,h);
 	}
 	
 }
 void*qsthreadwork(void*paras)
 {
 	int*data=(int*)paras;
 	time_t start=time(NULL);

 	quicksort(data,0,size/2-1);
 	time_t end=time(NULL);
 	int duration=end-start;
 	printf("Time taken for QuickSort: %d min %d secs\n",duration/60,duration%60);
 	FILE*fname=fopen("firsthalf.txt","w");
 	for(int i=0;i<size/2;i++)
 	{
 		fprintf(fname,"%d\n",data[i]);
 	}
 	fclose(fname);
 	pthread_exit(NULL);
 }
 void insertionsort(int data[],int l,int h)
 {
 	for(int i=l+1;i<=h;i++)
 	{
 		int key=data[i];
 		int j=i-1;
 		while(j>=l && data[j]>key)
 		{
 			data[j+1]=data[j];
 			j--;
 		}
 		data[j+1]=key;
 	}
 	
 }
 void*isthreadwork(void*paras)
 {
 	int*data=(int*)paras;
 	time_t start=time(NULL);
 	insertionsort(data,size/2,size-1);
 	time_t end=time(NULL);
 	int duration=end-start;
 	printf("Time taken for InsertionSort: %d min %d secs\n",duration/60,duration%60);
 	FILE*fname=fopen("secondhalf.txt","w");
 	for(int i=size/2;i<size;i++)
 	{
 		fprintf(fname,"%d\n",data[i]);
 	}
 	fclose(fname);
 	pthread_exit(NULL);
 }
 int main()
 {
 	printf("%d\n",size);
 	srand(time(NULL));
 	int data[50000];
 	for(int i=0;i<size;i++)
 	{
		data[i]=rand()%100;
 	}
 	pthread_t qsthread,isthread;
 	pthread_create(&qsthread,NULL,qsthreadwork,(void*)data);
 	pthread_join(qsthread,NULL);
 	pthread_create(&isthread,NULL,isthreadwork,(void*)data);
 	pthread_join(isthread,NULL);
 	//free(data);
 	return 0;
 }
