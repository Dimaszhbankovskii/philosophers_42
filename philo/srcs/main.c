#include "../includes/philosophers.h"

static void	simulation(t_data *data, t_philo *philos)
{
	int	i;
	int	philos_ate;

	while (!data->death)
	{
		usleep(3000);
		i = 0;
		philos_ate = 0;
		while (i < data->args.num_philos && !data->death)
		{
			pthread_mutex_lock(&philos[i].condition_mutex);
			if (get_time() > philos[i].die_time)
			{
				print_mutex(&philos[i], DIE);
				data->death = 1;
			}
			if (philos[i].count_meals >= data->args.num_meals)
				philos_ate++;
			pthread_mutex_unlock(&philos[i].condition_mutex);
			i++;
		}
		if (data->args.num_meals > 0 && philos_ate == data->args.num_philos)
			data->death = 1;
	}
}

static int	philo_thread(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	data->start_program = get_time();
	while (i < data->args.num_philos)
	{
		philos[i].die_time = data->start_program + data->args.time_to_die;
		if (pthread_create(&philos[i].pid_pthread, NULL, \
		&philo_life, &philos[i]))
			return (1);
		i++;
	}
	simulation(data, philos);
	i = 0;
	while (i < data->args.num_philos)
	{
		pthread_join(philos[i].pid_pthread, NULL);
		i++;
	}
	return (0);
}

static int	unique_philo_thread(t_data *data, t_philo *philo)
{
	data->start_program = get_time();
	philo->die_time = data->start_program + data->args.time_to_die;
	if (pthread_create(&(philo->pid_pthread), NULL, \
	&unique_philo_life, philo))
		return (1);
	pthread_join(philo->pid_pthread, NULL);
	return (0);
}

static int	start_proccess(t_data *data, t_philo *philos)
{
	if (data->args.num_philos == 1)
	{
		if (unique_philo_thread(data, philos))
		{
			clear_all(data, philos);
			return (1);
		}
	}
	else
	{
		if (philo_thread(data, philos))
		{
			clear_all(data, philos);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (write_error(ERROR_NUM_ARGS, 1));
	if (validation_input_data(argc, argv))
		return (write_error(ERROR_INVALID_ARGS, 1));
	if (init_data(&data, &philos, argc, argv))
		return (1);
	if (start_proccess(data, philos))
		return (1);
	clear_all(data, philos);
	return (0);
}
