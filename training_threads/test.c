#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_data
{
	int				num;
	int				id;
	pthread_mutex_t	mutex;
}				t_data;

void	*process(void *data)
{
	t_data	*tmp;
	int		i;

	tmp = (t_data *)data;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&(tmp->mutex));
		tmp->id++;
		while (i < 5)
		{
			tmp->num++;
			printf("thread = %d    num = %d\n", tmp->id, tmp->num);
			i++;
		}
		if (i > 0)
			break ;
	}
	pthread_mutex_unlock(&(tmp->mutex));
	return (NULL);
}

int	main(void)
{
	t_data		data;
	int			num_pthread;
	int			i;
	pthread_t	pthread_id;

	data.num = 0;
	data.id = 0;
	pthread_mutex_init(&data.mutex, NULL);
	num_pthread = 3;
	i = 0;
	while (i < num_pthread)
	{
		if (pthread_create(&pthread_id, NULL, &process, (void *) &data))
			return (1);
		i++;
	}
	pthread_detach(pthread_id);
	usleep(1000);
	pthread_mutex_lock(&data.mutex);
	printf("num = %d\n", data.num);
	pthread_mutex_unlock(&data.mutex);
	return (0);
}
