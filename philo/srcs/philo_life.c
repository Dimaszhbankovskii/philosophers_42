#include "../includes/philosophers.h"

static void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	print_mutex(philo, TAKE_FORK);
	pthread_mutex_lock(philo->fork2);
	print_mutex(philo, TAKE_FORK);
	pthread_mutex_lock(&(philo->condition_mutex));
	print_mutex(philo, EATING);
	philo->die_time = get_time() + philo->args.time_to_die;
	philo->count_meals++;
	pthread_mutex_unlock(&(philo->condition_mutex));
	if (!philo->data->death)
		ft_sleep(philo->args.time_to_eat);
		// usleep(philo->args.time_to_eat * 1000); // кастомный usleep
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
}

void	*philo_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->data->death)
	{
		philo_eating(philo);
		print_mutex(philo, SLEEPING);
		if (!philo->data->death)
			ft_sleep(philo->args.time_to_sleep);
			// usleep(philo->args.time_to_sleep * 1000); // кастомный usleep
		print_mutex(philo, THINKING);
	}
	return (NULL);
}

void	*unique_philo_life(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(philo->fork1);
	print_mutex(philo, TAKE_FORK);
	usleep(philo->args.time_to_die * 1000); // кастомный usleep
	print_mutex(philo, DIE);
	pthread_mutex_unlock(philo->fork1);
	return (NULL);
}
