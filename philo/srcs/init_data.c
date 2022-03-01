#include "../includes/philosophers.h"

int	init_forks(t_fork *forks, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		forks[i].id_fork = i + 1;
		forks[i].is_busy = 0;
		if (pthread_mutex_init(&(forks[i].mutex), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_philosopher(t_philosopher *philos, t_data *data, t_fork *forks)
{
	int			i;
	pthread_t	id_pthread;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id_philo = i + 1;
		philos[i].num_eating = 0;
		philos[i].left_fork = forks + i;
		philos[i].right_fork = forks + (i + 1) % data->num_philos;
		philos[i].stdout_mutex = &data->stdout_mutex;
		if (pthread_mutex_init(&philos[i].condition_philo, NULL))
			return (1);
		// philos[i].last_eating = 
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		if (pthread_create(&id_pthread, NULL, &func, &philos[i]))
			return (1);
		i++;
	}
	pthread_detach(id_pthread);
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->num_philos < 1 || data->time_to_die < 0 || \
	data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (1);
	if (argc == 6)
	{
		data->num_eating = ft_atoi(argv[5]);
		if (data->num_eating <= 0)
			return (1);
	}
	else
		data->num_eating = -1;
	if (pthread_mutex_init(&(data->stdout_mutex), NULL))
		return (1);
	return (0);
}