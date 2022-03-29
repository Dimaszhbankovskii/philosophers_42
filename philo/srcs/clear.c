#include "../includes/philosophers.h"

void	clear_forks(t_data *data, int n)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < n)
		{
			pthread_mutex_destroy(&(data->forks[i].fork_mutex));
			i++;
		}
		free (data->forks);
		data->forks = NULL;
	}
}

void	clear_data_mutex(t_data *data)
{
	pthread_mutex_destroy(&(data->mutex_stdout));
	pthread_mutex_destroy(&(data->mutex_death));
	pthread_mutex_destroy(&(data->mutex_all_ate));
}

void	clear_philos(t_philo *philos, int n)
{
	int	i;
	if (philos)
	{
		i = 0;
		while (i < n)
		{
			pthread_mutex_destroy(&(philos[i].condition_mutex));
			i++;
		}
		free (philos);
		philos = NULL;
	}
}

void	clear_all(t_data *data, t_philo *philos)
{
	if (philos)
		clear_philos(philos, data->args.num_philos);
	if (data)
	{
		clear_data_mutex(data);
		clear_forks(data, data->args.num_philos);
		free (data);
	}
}
