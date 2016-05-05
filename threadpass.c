#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

struct thread_pass {
	pthread_mutex_t server;
	pthread_mutex_t clients;
	pthread_cond_t done;

	int work;
	void *data;
};

struct thread_pass *
thread_pass_new(void *data)
{
	struct thread_pass *p = malloc(sizeof(*p));

	 pthread_mutex_init(&p->server, NULL);
	 pthread_mutex_init(&p->clients, NULL);
	 pthread_cond_init (&p->done, NULL);
	 p->data = data;
	 p->work = 0;
	 return p;
}

void
thread_pass_free(struct thread_pass *p)
{
	pthread_mutex_destroy(&p->server);
	pthread_mutex_destroy(&p->clients);
	pthread_cond_destroy(&p->done);
	free(p);
}

void *
thread_pass_get(struct thread_pass *p)
{
	pthread_mutex_lock(&p->clients);
	return p->data;

}

void
thread_pass_return(struct thread_pass *p)
{
	p->work = 1;
	pthread_cond_wait(&p->done, &p->server);
	pthread_mutex_unlock(&p->clients);
}

void
thread_pass_continue(struct thread_pass *p)
{
	p->work = 0;
	pthread_cond_signal(&p->done);
}
