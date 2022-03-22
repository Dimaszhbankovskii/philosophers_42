#include "../includes/philosophers.h"

int	philo_eating(t_philo *philo)
{
	t_fork	*min_fork;
	t_fork	*max_fork;

	min_fork = philo->right_fork;
	max_fork = philo->left_fork;
	if (philo->right_fork->id_fork > philo->left_fork->id_fork)
	{
		min_fork = philo->left_fork;
		max_fork = philo->right_fork;
	}
	pthread_mutex_lock(&(min_fork->fork_mutex));
	print_mutex(philo, TAKE_FORK);
	pthread_mutex_lock(&(max_fork->fork_mutex));
	print_mutex(philo, TAKE_FORK);
	print_mutex(philo, EATING);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&(philo->condition_mutex));
	philo->count_meals++;
	philo->last_eating = get_time();
	pthread_mutex_unlock(&(philo->condition_mutex));
	pthread_mutex_unlock(&(max_fork->fork_mutex));
	pthread_mutex_unlock(&(min_fork->fork_mutex));
	return (0);
}

int	philo_sleeping(t_philo *philo)
{
	print_mutex(philo, SLEEPING);
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

int	philo_thinking(t_philo *philo)
{
	print_mutex(philo, THINKING);
	return (0);
}

void	*philo_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id_philo % 2 == 0)
		usleep(2500);
	while (!philo->data->death)
	{
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	return (0);
}
