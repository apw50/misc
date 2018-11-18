#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

pthread_t thread1, thread2, thread3;
pthread_mutex_t mutex;
pthread_mutexattr_t mutexattr;
int policy = SCHED_RR;
int priority = 6;
struct sched_param param;

void callFunc() {
	printf("in callFunc");
}

void func1() {
	pthread_mutex_lock(&mutex);
	printf("entering func1");
	printf("exiting func1");
	pthread_mutex_unlock(&mutex);
}

void func2() {
	pthread_mutex_lock(&mutex);
	printf("entering func2");
	callFunc();
	printf("exiting func2");
	pthread_mutex_unlock(&mutex);
}

void func3() {
	pthread_mutex_lock(&mutex);
	printf("entering func3");
	printf("exiting func3");
	pthread_mutex_unlock(&mutex);
}

int main() {
	//create mutex and initialize it.
	//create thread 1, thread 2 and thread 3
	//set different priority for each thread
	//set handler for thread 1, thread 2 and thread 3 respectively. For instance, function 1 for thread 1, function 2 for thread 2 and function 3 for thread 3
	
	pthread_mutexattr_setprotocol(&mutexattr, PTHREAD_PRIO_INHERIT);
	pthread_mutex_init(&mutex, &mutexattr);
	priority = sched_get_priority_max(policy);
	param.sched_priority = priority;
	pthread_setschedparam(thread1, policy,&param);
	pthread_join(thread1,NULL);
	return 0;
}