#include "../includes/philosophers.h"

int	validation_input_data(int argc, char **argv)
{
	// написать проверку на символы
	return (0);
}

int	init_philos(t_philo **philos, t_data *data)
{
	t_philo	*tmp;
	int		i;

	tmp = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!tmp)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		tmp[i].id_philo = i + 1;
		tmp[i].count_meals = 0;
		tmp[i].data = data;
		tmp[i].right_fork = data->forks + i;
		tmp[i].left_fork = data->forks + (i + 1) % data->num_philos;
		if (pthread_mutex_init(&(tmp[i].condition_mutex), NULL))
			return (1);
		i++;
	}
	*philos = tmp;
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		data->forks[i].id_fork = i + 1;
		if (pthread_mutex_init(&(data->forks[i].fork_mutex), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data **data, int argc, char **argv)
{
	*data = (t_data *)malloc(sizeof(t_data));
	if (!(*data))
		return (1);
	(*data)->num_philos = ft_atoi(argv[1]);
	(*data)->time_to_die = ft_atoi(argv[2]);
	(*data)->time_to_eat = ft_atoi(argv[3]);
	(*data)->time_to_sleep = ft_atoi(argv[4]);
	if ((*data)->num_philos < 1 || (*data)->time_to_die < 0 || \
	(*data)->time_to_eat < 0 || (*data)->time_to_sleep < 0)
		return (1);
	if (argc == 6)
	{
		(*data)->num_meals = ft_atoi(argv[5]);
		if ((*data)->num_meals <= 0)
			return (1);
	}
	else
		(*data)->num_meals = -1;
	(*data)->death = 0;
	if (pthread_mutex_init(&((*data)->stdout_mutex), NULL))
		return (1);
	(*data)->forks = NULL;
	return (0);
}
