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

void	ft_sleep(long long time_ms)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time();
	current_time = start_time;
	while (current_time - start_time < time_ms)
	{
		usleep(50);
		current_time = get_time();
	}
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
	if (!philo->data->death)
		printf("\033[0;37m%5lld\033[0m \033[1;36m%d\033[0m %s\n", \
		get_time() - philo->data->start_program, philo->id_philo + 1, mess);
	pthread_mutex_unlock(&(philo->data->mutex_stdout));
}
