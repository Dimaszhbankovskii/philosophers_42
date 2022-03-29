#include "../includes/philosophers.h"

int	take_forks(t_philo *philo)
{
	// сделать проверку, что философы живы
	if (!check_condition_philo(philo))
		return (0);
	if (philo->first_right)
	{
		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
		print_mutex(philo, TAKE_FORK);
		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
		print_mutex(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&(philo->left_fork->fork_mutex));
		print_mutex(philo, TAKE_FORK);
		pthread_mutex_lock(&(philo->right_fork->fork_mutex));
		print_mutex(philo, TAKE_FORK);
	}
	return (1);
}

int	drop_forks(t_philo *philo)
{
	if (philo->first_right)
	{
		pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
		pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
	}
	else
	{
		pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
		pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
	}
	return (0);
}

int	philo_eating(t_philo *philo)
{
	if (take_forks(philo))
		return (0);
	print_mutex(philo, EATING);
	pthread_mutex_lock(&(philo->condition_mutex));
	philo->count_meals++;
	philo->last_eating = get_time();
	pthread_mutex_unlock(&(philo->condition_mutex));
	usleep(philo->args.time_to_eat);
	drop_forks(philo);
	return (1);
}
