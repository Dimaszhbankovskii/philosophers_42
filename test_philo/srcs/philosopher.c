# include "../includes/philosopher.h"

long	current_time(void)
{
	struct timeval	tv;
	long			time_in_milliseconds;

	gettimeofday(&tv, NULL);
	time_in_milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_milliseconds);
}

static void	ft_message(t_env *env, int id, char *status)
{
	pthread_mutex_lock(&env->print_mutex);
	if (!env->stop)
		printf("%ld %d %s\n", current_time() - env->start_time, id + 1, status);
	pthread_mutex_unlock(&env->print_mutex);
}

static int	take_forks_and_eat(t_env *env, int id, int n1, int n2)
{
	pthread_mutex_lock(&env->forks[n1]);  // берем первую вилку
	ft_message(env, id, "has taken a fork");
	if (env->n == 1)	// проверка на 1 философа, но будет в отдельной ветке
		return (1);
	pthread_mutex_lock(&env->forks[n2]); // вторая вилка
	pthread_mutex_lock(&env->ph[id].eat_mutex); // мьютекс состояния
	ft_message(env, id, "has taken a fork");
	env->ph[id].die_at = current_time() + env->time_to_die; // обновление времени смерти
	env->ph[id].times_to_eat++;	// количество обедов
	ft_message(env, id, "is eating");
	pthread_mutex_unlock(&env->ph[id].eat_mutex);
	if (!env->stop) 
		usleep(env->time_to_eat); // ест
	pthread_mutex_unlock(&env->forks[n1]); // кладет вилки
	pthread_mutex_unlock(&env->forks[n2]);
	return (0);
}

void	*philosopher(void *arg)
{
	int		id;
	int		n1;
	int		n2;
	t_env	*env;
	t_phil	*ph;

	ph = (t_phil *)arg; // указатель на структуру философа
	env = (t_env *)ph->env_address; // указатель на гравную структуру
	id = ph->id;	// id философа
	n1 = (id + id % 2) % env->n;		// номер вилки 1
	n2 = (id + 1 - id % 2) % env->n;	// номер вилки 2
	while (!env->stop)
	{
		if (take_forks_and_eat(env, id, n1, n2) != 0)
			return (NULL);
		ft_message(env, id, "is sleeping");
		if (!env->stop)
			usleep(env->time_to_sleep);
		ft_message(env, id, "is thinking");
	}
	return (arg);
}
