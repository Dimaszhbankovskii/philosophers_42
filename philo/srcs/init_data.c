#include "../includes/philosophers.h"

static int	define_data(t_data *data, int argc, char **argv)
{
	data->args.num_philos = ft_atoi(argv[1]);
	data->args.time_to_die = ft_atoi(argv[2]);
	data->args.time_to_eat = ft_atoi(argv[3]);
	data->args.time_to_sleep = ft_atoi(argv[4]);
	if (data->args.num_philos < 1 || data->args.time_to_die < 0 || \
	data->args.time_to_eat < 0 || data->args.time_to_sleep < 0)
		return (1);
	if (argc == 6)
	{
		data->args.num_meals = ft_atoi(argv[5]);
		if (data->args.num_meals <= 0)
			return (1);
	}
	else
		data->args.num_meals = -1;
	data->death = 0;
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = (t_mutex *)malloc(sizeof(t_mutex) * \
	data->args.num_philos);
	if (!data->forks)
		return (-1);
	i = 0;
	while (i < data->args.num_philos)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (i);
		i++;
	}
	return (0);
}

static int	define_forks(t_data *data)
{
	int	res;

	res = init_forks(data);
	if (res)
	{
		clear_forks(data, res);
		return (1);
	}
	return (0);
}

static int	parsing_data(t_data *data, int argc, char **argv)
{
	if (define_data(data, argc, argv))
		return (write_error(ERROR_INVALID_VALUE_DATA, 1));
	if (define_forks(data))
		return (write_error(ERROR_INIT_FORKS, 1));
	if (pthread_mutex_init(&(data->mutex_stdout), NULL))
	{
		clear_forks(data, data->args.num_philos);
		return (write_error(ERROR_DATA_MUTEX, 1));
	}
	return (0);
}

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
