#include "../includes/philosophers.h"

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_atoi(char const *str)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	i = 0;
	num = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

long long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_mutex(t_philo *philo, char *mess)
{
	pthread_mutex_lock(&(philo->data->mutex_stdout));
	pthread_mutex_lock(&(philo->data->mutex_death));
	if (!philo->data->death)
		printf("\033[1;37m[%lld] \033[1;36m%d %s\n", 
		get_time() - philo->data->start_program, philo->id_philo, mess);
	pthread_mutex_unlock(&(philo->data->mutex_death));
	pthread_mutex_unlock(&(philo->data->mutex_stdout));
}
