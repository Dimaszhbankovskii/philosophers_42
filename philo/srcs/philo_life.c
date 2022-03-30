#include "../includes/philosophers.h"

static int	check_condition_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_death));
	if (philo->data->death)
	{
		pthread_mutex_unlock(&(philo->data->mutex_death));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->mutex_death));
	// pthread_mutex_lock(&(philo->data->mutex_all_ate));
	// if (philo->data->all_ate)
	// {
	// 	pthread_mutex_unlock(&(philo->data->mutex_all_ate));
	// 	return (0);
	// }
	// pthread_mutex_unlock(&(philo->data->mutex_all_ate));
	return (1);
}

// void	update_time_last_meal(t_philo *philo, int flag)
// {
// 	philo->last_eating = philo->last_eating + 
// 	(philo->) * flag;
// }

static void	philo_eating(t_philo *philo)
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
	pthread_mutex_lock(&min_fork->fork_mutex);
	print_mutex(philo, TAKE_FORK);
	pthread_mutex_lock(&max_fork->fork_mutex);
	print_mutex(philo, TAKE_FORK);
	print_mutex(philo, EATING);
	pthread_mutex_lock(&(philo->condition_mutex));
	philo->count_meals++;
	philo->last_eating = get_time();
	pthread_mutex_unlock(&(philo->condition_mutex));
	ft_sleep(philo->args.time_to_eat);
	pthread_mutex_unlock(&max_fork->fork_mutex);
	pthread_mutex_unlock(&min_fork->fork_mutex);
}

void	*philo_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id_philo % 2 == 0)
		usleep(2500);
	while (1)
	{
		if (!check_condition_philo(philo))
			break ;
		philo_eating(philo);
		print_mutex(philo, SLEEPING);
		ft_sleep(philo->args.time_to_sleep);
		print_mutex(philo, THINKING);
	}
	return (NULL);
}

void	*unique_philo_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(&philo->right_fork->fork_mutex);
	print_mutex(philo, TAKE_FORK);
	ft_sleep(philo->args.time_to_die);
	print_mutex(philo, "was died");
	pthread_mutex_unlock(&philo->right_fork->fork_mutex);
	return (NULL);
}
