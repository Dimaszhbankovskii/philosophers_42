#include "../includes/philosophers.h"

int	init_data(t_data **data, t_philo **philos, int argc, char **argv)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!*data)
		return (write_error(ERROR_MALLOC_DATA, 1));
	if (parsing_data(*data, argc, argv))
	{
		free (*data);
		return (1);
	}
	*philos = (t_philo *)malloc(sizeof(t_philo) * \
	(*data)->args.num_philos);
	if (!*philos)
	{
		clear_all(*data, NULL);
		return (write_error(ERROR_MALLOC_PHILOS, 1));
	}
	if (parsing_philos(*philos, *data))
	{
		clear_all(*data, NULL);
		return (write_error(ERROR_INIT_PHILOS, 1));
	}
	return (0);
}

// int	philo_was_died(t_data *data, t_philo *philo)
// {
// 	pthread_mutex_lock(&(philo->condition_mutex));
// 	if (get_time() - philo->last_eating >= data->time_to_die)
// 	{
// 		pthread_mutex_unlock(&(philo->condition_mutex));
// 		return (1);
// 	}
// 	pthread_mutex_unlock(&(philo->condition_mutex));
// 	return (0);
// }

// int	check_meals(t_data *data, t_philo *philo)
// {
// 	pthread_mutex_lock(&(philo->condition_mutex));
// 	if (philo->count_meals >= )
// 	return (0);
// }

// int	simulation(t_data *data, t_philo *philos)
// {
// 	int	i;

// 	while (1)
// 	{
// 		while (i < data->num_philos)
// 		i = 0;
// 		{
// 			if (philo_was_died(data, &philos[i]))
// 			{
// 				print_mutex(&philos[i], "was died");
// 				pthread_mutex_lock(&data->mutex_death);
// 				data->death = 1;
// 				pthread_mutex_unlock(&data->mutex_death);
// 				return (0);
// 			}
// 			// if (data->num_meals > 0)
// 			// {
// 			// 	if (check_meals(data, &philo[i]))
// 			// 		return (0);
// 			// }
// 			i++;
// 		}
// 	}
// 	return (0);
// }

// int	start_thread(t_data *data, t_philo *philos)
// {
// 	int	i;

// 	i = 0;
// 	data->start_program = get_time();
// 	while (i < data->num_philos)
// 	{
// 		philos[i].last_eating = get_time();
// 		if (pthread_create(&(philos[i].pid_pthread), NULL,
// 		&philo_life, &(philos[i])))
// 			return (1);
// 		pthread_detach(philos[i].pid_pthread);
// 		i++;
// 	}
// 	return (0);
// }

//
	void	*func(void *args)
	{
		(void) args;
		usleep(100000);
		printf("check\n");
		return (NULL);
	}
//

int	unique_philo_thread(t_data *data, t_philo *philo)
{
	data->start_program = get_time();
	philo->last_eating = data->start_program;
	if (pthread_create(&(philo->pid_pthread), NULL, \
	&unique_philo_life, philo))
		return (1);
	pthread_join(philo->pid_pthread, NULL);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;
	// int		i;

	if (argc < 5 || argc > 6)							// +
		return (write_error(ERROR_NUM_ARGS, 1));
	if (validation_input_data(argc, argv))				// +
		return (write_error(ERROR_INVALID_ARGS, 1));
	if (init_data(&data, &philos, argc, argv))			// +
		return (1);

	if (data->args.num_philos == 1)
	{
		if (unique_philo_thread(data, philos))
		{
			clear_all(data, philos);
			return (1);
		}
	}

	// if (start_thread(data, philos))
	// {
	// 	clear_all(data, philos);
	// 	return (1);
	// }

	// simulation(data, philos);

	clear_all(data, philos);
	return (0);
}
