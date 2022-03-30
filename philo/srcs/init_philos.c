#include "../includes/philosophers.h"

static int	init_philos(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.num_philos)
	{
		philos[i].args.num_philos = data->args.num_philos;
		philos[i].args.time_to_die = data->args.time_to_die;
		philos[i].args.time_to_eat = data->args.time_to_eat;
		philos[i].args.time_to_sleep = data->args.time_to_sleep;
		philos[i].args.num_meals = data->args.num_meals;
		philos[i].id_philo = i + 1;
		philos[i].count_meals = 0;
		philos[i].data = data;
		if (i == data->args.num_philos - 1)
			philos[i].first_right = 0;
		else
			philos[i].first_right = 1;
		philos[i].right_fork = data->forks + i;
		philos[i].left_fork = data->forks + (i + 1) % data->args.num_philos;
		if (pthread_mutex_init(&(philos[i].condition_mutex), NULL))
			return (i);
		i++;
	}
	return (0);
}

int	parsing_philos(t_philo *philos, t_data *data)
{
	int	res;

	res = init_philos(philos, data);
	if (res)
	{
		clear_philos(philos, res);
		return (1);
	}
	return (0);
}
