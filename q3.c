#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/select.h>
int flag=0;
int kbhit()
{
	struct timeval tv={0,0};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO,&fds);
	return select(STDIN_FILENO+1,&fds,NULL,NULL,&tv)>0;
}
void*indicator(void*paras)
{
	srand(time(NULL));
	flag=rand()%2;
	pthread_exit(NULL);
}
void*printer(void*paras)
{
	if(!flag)
		printf("Red Light\n");
	else
		printf("Green Light\n");
	pthread_exit(NULL);	
}
int main()
{
	int gameflag=0;
	char input;
	int score=0;
	while(!gameflag)
	{
		pthread_t threadid;
		pthread_create(&threadid,NULL,indicator,NULL);
		pthread_join(threadid,NULL);
		pthread_create(&threadid,NULL,printer,NULL);
		pthread_join(threadid,NULL);
		float st=(rand()%1000)/1000.0f+1.0f;
		usleep(st*1000000);
		if(kbhit())
		{
			input=getchar();
			if(input=='\n' && flag)
				score++;
			else
				gameflag=1;
			   
		}
	}
	printf("Game is Over!\nSCORE: %d\n",score);
	return 0;
	
}
//nope as i have checked as to whether the light is green and enter is pressed then the score will increment but the loop will continue as gameflag is 0, it will continue ro run unless enter is pressed with the flag being 0 indicating a red light that will cause the while loop to quit
