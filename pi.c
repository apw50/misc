#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

pthread thread1, thread2, thread3;
pthread_mutex_t mutex;
pthread_mutexattr_t mutexattr;
int policy = SCHED_RR;
int priority = 6;
struct sched_param param;

void callFunc()
{
	//do some work here.
}

void funtion1() {
	pthread_mutex_lock(&mutex);
	
	//function 1 for thread 1.
	//do some work here
	pthread_mutex_unlock(&mutex);
}

void function2()
{
	//function 2 for thread 2.
	//do some work here and callFunc()
	
	callFunc()
}

void function3()
{
	//function 3 for thread 3.
	//do some work here
}

void main()
{
	//create mutex and initialize it.
	//create thread 1, thread 2 and thread 3
	//set different priority for each thread
	//set handler for thread 1, thread 2 and thread 3 respectively. For instance, function 1 for thread 1, function 2 for thread 2 and function 3 for thread 3
}