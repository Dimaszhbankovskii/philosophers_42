#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR_NUM_ARGS "Error: invalid number of arguments"
# define ERROR_INVALID_ARGS "Error: invalid input arguments"
# define ERROR_MALLOC_DATA "Error: malloc data"
# define ERROR_INVALID_VALUE_DATA "Error: invalid value of arguments"
# define ERROR_INIT_FORKS "Error: init forks"
# define ERROR_DATA_MUTEX "Error: init data mutex"
# define ERROR_MALLOC_PHILOS "Error: malloc philos"
# define ERROR_INIT_PHILOS "Error: init philos"

# define TAKE_FORK "\033[1;34mhas taking a fork\033[0m"
# define EATING "\033[1;32mis eating\033[0m"
# define SLEEPING "\033[1;35mis sleeping\033[0m"
# define THINKING "\033[1;36mis thinking\033[0m"
# define DIE "\033[1;31mdied\033[0m"

typedef pthread_mutex_t	t_mutex;

typedef struct s_args
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;
}				t_args;

typedef struct s_data
{
	t_args			args;
	int				death;
	long long int	start_program;
	t_mutex			mutex_stdout;
	t_mutex			*forks;
}				t_data;

typedef struct s_philo
{
	t_args			args;
	int				id_philo;
	int				count_meals;
	long long int	die_time;
	t_data			*data;
	t_mutex			*fork1;
	t_mutex			*fork2;
	t_mutex			condition_mutex;
	pthread_t		pid_pthread;
}				t_philo;

int			validation_input_data(int argc, char **argv);
int			init_data(t_data **data, t_philo **philos, int argc, char **argv);
int			parsing_philos(t_philo *philos, t_data *data);

void		*unique_philo_life(void *args);
void		*philo_life(void *args);

void		clear_all(t_data *data, t_philo *philos);
void		clear_philos(t_philo *philos, int n);
void		clear_forks(t_data *data, int n);

int			write_error(char *mess, int code);
size_t		ft_strlen(char const *str);
int			ft_atoi(char const *str);
long long	get_time(void);
void		ft_sleep(long long time_ms);
void		print_mutex(t_philo *philo, char *mess);

#endif