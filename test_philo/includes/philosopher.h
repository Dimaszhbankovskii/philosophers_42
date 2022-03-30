#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define USAGE_MSG "Usage: mess\n"

struct	s_env;

typedef struct s_phil
{
	pthread_t		th;				// pid потока
	pthread_mutex_t	eat_mutex;		// мьютекс на проверку состояния философа
	int				id;				// id философа
	struct s_env	*env_address;	// указатель на главную структуру
	int				times_to_eat;	// количество обедов поел
	long			die_at;			// время смерти
}				t_phil;

typedef struct s_env
{
	t_phil			*ph;			// указатель на массив философов
	pthread_mutex_t	*forks;			// указатель на массив вилос
	volatile int	stop;			// флаг окончания
	// int			stop;			// как вариант int работает
	pthread_mutex_t	print_mutex;	// мьютекс на STDOUT
	int				n;				// число философов
	int				time_to_die;	// время смерти в мс
	int				time_to_eat;	// время на еду в мкс
	int				time_to_sleep;	// время на сон в мкс
	int				n_times_to_eat;	// количество обедов
	long			start_time;		// время начала программы
}				t_env;

void	*philosopher(void *arg);
long	current_time(void);

#endif