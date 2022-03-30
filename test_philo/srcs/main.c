# include "../includes/philosopher.h"

static int	ft_atoi_pos(const char *str)
{
	int	res;

	res = 0;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			return (-1);
	while ('0' <= *str && *str <= '9')
		res = res * 10 + *str++ - '0';
	if (*str != '\0')
		return (-1);
	return (res);
}

static int	ft_args(int argc, char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (i < argc)	// привека валидности
		if (ft_atoi_pos(argv[i++])<= 0)
			return (1);
	// инициализация параметров входных
	env->n = ft_atoi_pos(argv[1]);
	env->time_to_die = ft_atoi_pos(argv[2]);
	env->time_to_eat = ft_atoi_pos(argv[3]) * 1000;
	env->time_to_sleep = ft_atoi_pos(argv[4]) * 1000;
	if (argc == 6)
		env->n_times_to_eat = ft_atoi_pos(argv[5]);
	else
		env->n_times_to_eat = -1;
	// массив вилок
	env->forks = malloc(env->n * sizeof(*env->forks));
	if (env->forks == NULL)
		return (1);
	// массив философов
	env->ph = malloc(env->n * sizeof(*env->ph));
	if (env->ph == NULL)
	{
		free(env->forks);
		return (1);
	}
	return (0);
}

static int	ft_init(t_env *env)
{
	int	i;

	env->stop = 0;	// флаг остановки
	env->start_time = current_time();	// время старта программы
	i = -1;
	while (++i < env->n)
	{
		env->ph[i].id = i;				// id философа
		env->ph[i].env_address = env;	// указатель на главную структуру
		env->ph[i].times_to_eat = 0;	// количество обедов поел
		env->ph[i].die_at = env->start_time + env->time_to_die; // следующее время смерти
		pthread_mutex_init(&env->forks[i], NULL);			// мьютекс на вилку
		pthread_mutex_init(&env->ph[i].eat_mutex, NULL);	// мьютекс ???
	}
	pthread_mutex_init(&env->print_mutex, NULL);	// мьютекс на STDOUT
	i = -1;
	// создание потоков
	while (++i < env->n)
		if (pthread_create(&env->ph[i].th, NULL, &philosopher, &env->ph[i]))
			return (1);
	return (0);
}

static void	ft_monitoring(t_env *env)
{
	int	i;
	int	j;

	// бесконечный цикл до флага stop
	while (!env->stop)
	{
		// малый интервал остановки (потестить разные значения и кастом слип)
		usleep(3000);
		j = 0;
		i = -1;
		// проход по философам
		while (++i < env->n && !env->stop)
		{
			// мьютекс на состояние философа
			pthread_mutex_lock(&env->ph[i].eat_mutex);
			if (current_time() > env->ph[i].die_at) // проверка времени и смерти
			{
				pthread_mutex_lock(&env->print_mutex);
				env->stop = 1;	// флаг смерти, вывод сообщения
				printf("%ld %d died\n", current_time() - env->start_time, i + 1);
				pthread_mutex_unlock(&env->print_mutex);
			}
			if (env->ph[i].times_to_eat >= env->n_times_to_eat)
				j++;  // подсчёт философов, которые наелись
			pthread_mutex_unlock(&env->ph[i].eat_mutex);
		}
		if (env->n_times_to_eat != -1 && j == env->n)
			env->stop = 1; // если все наелись флаг смерти
	}
}

int	main(int argc, char **argv)
{
	t_env	env; // главная структура
	int		i;
	int		res;

	// проверка количества аргументов и их валидности
	// инициализация входных данных, массив вилок и философов
	if ((argc != 5 && argc != 6) || ft_args(argc, argv, &env))
		return (1 + 0 * write(2, USAGE_MSG, 12));
	//
	if (ft_init(&env))
		return (2 + 0 * write(2, "Error 1\n", 8));
	ft_monitoring(&env);
	res = 0;
	i = -1;
	while (++i < env.n)
		if (pthread_join(env.ph[i].th, NULL))
			res = 3 + 0 * write(2, "Error 2\n", 8);
	i = -1;
	while (++i < env.n)
	{
		pthread_mutex_destroy(&env.forks[i]);
		pthread_mutex_destroy(&env.ph[i].eat_mutex);
	}
	pthread_mutex_destroy(&env.print_mutex);
	free (env.forks);
	free (env.ph);
	return (res);
}
