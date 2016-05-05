#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include "threadpass.h"

int var;

void *
server(void *arg)
{
	int var2;
	int count = 0;
	struct thread_pass *p = arg;

	while (1) {
		if (!p->work)
			continue;
		var2 = *(int *) p->data;
		thread_pass_continue(p);
		printf("%i\n", var2);
		++count;
		if (count == 4)
			pthread_exit(NULL);
	}
}

void *
client(void *arg)
{
	struct thread_pass *p = ((void **) arg)[0];
	int var2 = *((int *) ((void **) arg)[1]);

	*(int *) thread_pass_get(p) = var2;
	thread_pass_return(p);
	pthread_exit(NULL);
}

int
main(void)
{
	pthread_t s;
	pthread_t c1;
	pthread_t c2;
	pthread_t c3;
	pthread_t c4;
	int a1 = 1;
	int a2 = 2;
	int a3 = 3;
	int a4 = 4;
	struct thread_pass *p = thread_pass_new(&var);

	pthread_create(&c1, NULL, client, (void *[]) { p, &a1 });
	pthread_create(&c2, NULL, client, (void *[]) { p, &a2 });
	pthread_create(&c3, NULL, client, (void *[]) { p, &a3 });
	pthread_create(&c4, NULL, client, (void *[]) { p, &a4 });
	pthread_create(&s, NULL, server, p);


	pthread_join(s, NULL);
	pthread_join(c1, NULL);
	pthread_join(c2, NULL);
	pthread_join(c3, NULL);
	pthread_join(c4, NULL);
	thread_pass_free(p);
}
