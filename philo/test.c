#include <pthread.h>
#include <stdio.h>

int	main(void)
{
	pthread_mutex_t	mutex;

	// if (!pthread_mutex_init(&mutex, NULL))
	// 	printf("mutex init\n");
	// else
	// 	printf("error: mutex init\n");
	if (!pthread_mutex_destroy(&mutex))
		printf("mutex destoy\n");
	else
		printf("error: mutex destroy\n");
	return (0);
}
