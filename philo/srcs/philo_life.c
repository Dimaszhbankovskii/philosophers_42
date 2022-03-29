#include "../includes/philosophers.h"

int	check_condition_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_death));
	if (philo->data->death)
	{
		pthread_mutex_unlock(&(philo->data->mutex_death));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->mutex_death));
	pthread_mutex_lock(&(philo->data->mutex_all_ate));
	if (philo->data->all_ate)
	{
		pthread_mutex_unlock(&(philo->data->mutex_all_ate));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->mutex_all_ate));
	return (1);
}

int	philo_sleeping(t_philo *philo) // возможно нужна доп проверка, что философ жив
{
	if (!check_condition_philo(philo))
		return (0);
	print_mutex(philo, SLEEPING);
	usleep(philo->args.time_to_sleep);
	return (1);
}

int	philo_thinking(t_philo *philo) // возможно нужна доп проверка, что философ жив
{
	if (!check_condition_philo(philo))
		return (0);
	print_mutex(philo, THINKING);
	return (1);
}

void	*philo_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id_philo % 2 == 0)
		usleep(2500);
	while (1)
	{
		if (!philo_eating(philo))
			break ;
		if (!philo_sleeping(philo))
			break ;
		if (!philo_thinking(philo))
			break ;
	}
	return (NULL);
}

void	*unique_philo_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	print_mutex(philo, TAKE_FORK);
	usleep(philo->args.time_to_die * 1000);
	print_mutex(philo, "was died");
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	return (NULL);
}
