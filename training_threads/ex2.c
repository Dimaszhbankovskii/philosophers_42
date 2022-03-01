#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define ERROR_CREATE_THREAD 1
#define ERROR_JOIN_THREAD 2
#define BAD_MESSAGE 3
#define SUCCESS 0

typedef struct s_data
{
	int			id;
	char const	*mess;
	int			out;
}				t_data;

void	*hello_world(void *args)
{
	t_data	*arg;
	int		len;

	arg = (t_data *)args;
	if (arg->mess == NULL)
		return ((void *)BAD_MESSAGE);
	len = strlen(arg->mess);
	printf("%s\n", arg->mess);
	arg->out = len;
	return (SUCCESS);
}

#define NUM_THREADS 4

int	main(void)
{
	pthread_t	threads[NUM_THREADS];
	int			status;
	int			i;
	int			status_addr;
	t_data		args[NUM_THREADS];
	const char	*messages[] = {"First", NULL, "Third Message", "Fourth Message"};

	for (i = 0; i < NUM_THREADS; i++)
	{
		args[i].id = i;
		args[i].mess = messages[i];
	}
	for (i = 0; i < NUM_THREADS; i++)
	{
		status = pthread_create(&threads[i], NULL, &hello_world, (void*) &args[i]);
		if (status != 0)
		{
			printf("main error: can't create thread, status = %d\n", status);
			exit(ERROR_CREATE_THREAD);
		}
	}

	printf("Main Message\n");

	for (i = 0; i < NUM_THREADS; i++)
	{
		status = pthread_join(threads[i], (void**)&status_addr);
		if (status != SUCCESS) {
			printf("main error: can't join thread, status = %d\n", status);
			exit(ERROR_JOIN_THREAD);
		}
		printf("%d joined with address %d\n", i, status_addr);
	}
 
	for (i = 0; i < NUM_THREADS; i++) {
		printf("thread %d arg.out = %d\n", i, args[i].out);
	}
	return 0;
}