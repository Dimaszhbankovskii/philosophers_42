#include "../includes/philosophers.h"

int	monitoring_philos(t_philo *philos, t_data *data)
{
	int	i;
	int	philos_ate;

	while (!data->death)
	{
		philos_ate = 0;
		i = 0;
		while (i < data->num_philos)
		{
			if (get_time() - philos[i].last_eating > data->time_to_die)
			{
				print_mutex(&(philos[i]), "died");
				data->death = 1;
				break ;
			}
			if (data->num_meals != -1 && \
			philos[i].count_meals >= data->num_meals)
				philos_ate++;
			i++;
		}
		if (philos_ate == data->num_meals)
			data->death = 1;
	}
	return (0);
}

int	start_simulation(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	data->start_program = get_time();
	while (i < data->num_philos)
	{
		philo[i].last_eating = get_time();
		if (pthread_create(&(philo[i].pid_pthread), NULL, \
		&philo_life, philo + i))
			return (1);
		pthread_detach(philo[i].pid_pthread);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;
	
	if (argc < 5 || argc > 6)
		return (write_error(ERROR_NUM_ARGS));
	if (validation_input_data(argc, argv))
		return (write_error(ERROR_INVALID_DATA));
	if (init_data(&data, argc, argv))
		return (clear_data(data, NULL, ERROR_INIT_DATA));
	if (init_forks(data))
		return (clear_data(data, NULL, ERROR_INIT_FORKS));
	if (init_philos(&philos, data))
		return (clear_data(data, philos, ERROR_INIT_PHILOS));
	// start_simulation(philos, data);
	// monitoring_philos(philos, data);
	return (clear_data(data, philos, NULL));
}