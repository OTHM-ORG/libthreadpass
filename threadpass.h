/* Include these
 * #include <pthread.h>
 * #include <sched.h>
 * #include <stdio.h>
 * #include <stdlib.h>
 */

struct thread_pass {
	pthread_mutex_t server;
	pthread_mutex_t clients;
	pthread_cond_t done;

	int work;
	void *data;
};

struct thread_pass *thread_pass_new(void *data);
void thread_pass_free(struct thread_pass *p);
void thread_pass_continue(struct thread_pass *p);
void *thread_pass_get(struct thread_pass *p);
void thread_pass_return(struct thread_pass *p);


