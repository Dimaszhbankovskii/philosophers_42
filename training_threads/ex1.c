#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
 
#define ERROR_CREATE_THREAD 1
#define ERROR_JOIN_THREAD 2
#define SUCCESS 0
 
void	*helloWorld(void *args)
{
	(void)args;
	printf("Hello from thread!\n");
	return (SUCCESS);
}
 
int main(void)
{
	pthread_t	thread;
	int			status_addr;
 
    if (pthread_create(&thread, NULL, &helloWorld, NULL))
	{
		printf("main error: can't create thread\n");
		exit(ERROR_CREATE_THREAD);
	}

	printf("Hello 1 from main!\n");
	usleep(1000);
	printf("Hello 2 from main!\n");

	if (pthread_join(thread, (void**)&status_addr))
	{
		printf("main error: can't join thread\n");
		exit(ERROR_JOIN_THREAD);
	}
	printf("joined with address %d\n", status_addr);

	return 0;
}
