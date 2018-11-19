//gcc pi.c -o pi -pthread
//./pi

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
pthread_attr_t attr;

void
       display_sched_attr(int policy, struct sched_param *param)
       {
           printf("    policy=%s, priority=%d\n",
                   (policy == SCHED_FIFO)  ? "SCHED_FIFO" :
                   (policy == SCHED_RR)    ? "SCHED_RR" :
                   (policy == SCHED_OTHER) ? "SCHED_OTHER" :
                   "???",
                   param->sched_priority);
       }
void
       print_sched_info(char *msg)
       {
           int policy, s;
           struct sched_param param;

           s = pthread_getschedparam(pthread_self(), &policy, &param);

           printf("%s\n", msg);
           display_sched_attr(policy, &param);
       }

void callFunc() {
	printf("in callFunc\n");
	sleep(0.1);
}

void *func1() {
	pthread_mutex_lock(&mutex);
	printf("entering func1\n");

	printf("%d\n",pthread_self());
	print_sched_info("Thread1 Scheduler Attributes: ");
           
	sleep(0.1);
	printf("exiting func1\n");
	pthread_mutex_unlock(&mutex);
}

void *func2() {
	pthread_mutex_lock(&mutex);
	printf("entering func2\n");

	printf("%d\n",pthread_self());
	print_sched_info("Thread2 Scheduler Attributes: ");

	sleep(0.1);
	callFunc();
	printf("exiting func2\n");
	pthread_mutex_unlock(&mutex);
}

void *func3() {
	pthread_mutex_lock(&mutex);
	printf("entering func3\n");

	printf("%d\n",pthread_self());
	print_sched_info("Thread3 Scheduler Attributes: ");

	sleep(0.1);
	printf("exiting func3\n");
	pthread_mutex_unlock(&mutex);
}

int main() {
	//create mutex and initialize it.
	//create thread 1, thread 2 and thread 3
	//set different priority for each thread
	//set handler for thread 1, thread 2 and thread 3 respectively. For instance, function 1 for thread 1, function 2 for thread 2 and function 3 for thread 3
	printf("%d\n",pthread_self());
	print_sched_info("Main Scheduler Attributes: ");

	pthread_mutexattr_setprotocol(&mutexattr, PTHREAD_PRIO_INHERIT);
	pthread_mutex_init(&mutex, &mutexattr);
	//priority = sched_get_priority_max(policy);
	priority = 19;
	param.sched_priority = priority;

	pthread_create(&thread1,NULL,func1,NULL);
	pthread_create(&thread2,NULL,func2,NULL);
	pthread_create(&thread3,NULL,func3,NULL);

	pthread_setschedparam(thread1, policy,&param);
	pthread_setschedparam(thread2, policy,&param);
	pthread_setschedparam(thread3, policy,&param);
	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	return 0;
}