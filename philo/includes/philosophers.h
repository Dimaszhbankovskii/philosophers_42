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
# define THINKING "is thinking"

// # define ERROR_INVALID_DATA "Error: invalid value of arguments"
// # define ERROR_INIT_DATA "Error: init data"

// # define ERROR_INIT_PHILOS "Error: init philosophers"

typedef pthread_mutex_t t_mutex;

// num_philos - число философов (потоков)
// time_to_die - время до смерти (после последнего обеда)
// time_to_eat - время на обед
// time_to_sleep - время на сон
// num_meals - сколько раз должен поесть философ (доп. параметр)
typedef struct s_args
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;
}				t_args;

typedef struct s_fork
{
	int		id_fork;
	t_mutex	fork_mutex;
}				t_fork;

// deaht - флаг смерти философа
// all_ate - флаг, что все поели нужно число раз
// start_program - время начала программы
// mutex_stdout - мьютекс на STDOUT
// mutex_death - мьютекс на проверку флага смерти
// mutex_count_meals - мьютекс на счетчик обедов
typedef struct s_data
{
	t_args			args;
	int				death;
	int				all_ate;
	long long int	start_program;
	t_mutex			mutex_stdout;
	t_mutex			mutex_death;
	t_mutex			mutex_all_ate;
	t_fork			*forks;
}				t_data;

typedef struct s_philo
{
	t_args			args;
	int				id_philo;
	int				count_meals;
	long long int	last_eating;
	t_data			*data;
	int				first_right;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_mutex			condition_mutex;
	pthread_t		pid_pthread;
}				t_philo;

int		validation_input_data(int argc, char **argv);
int		parsing_data(t_data *data, int argc, char **argv); // +
int		parsing_philos(t_philo *philos, t_data *data); // +

void	*unique_philo_life(void *args);
void	*philo_life(void *args);
int		philo_eating(t_philo *philo);
int		check_condition_philo(t_philo *philo);


void	clear_all(t_data *data, t_philo *philos); // +
void	clear_philos(t_philo *philos, int n); // +
void	clear_forks(t_data *data, int n); // +
void	clear_data_mutex(t_data *data); // +

int		write_error(char *mess, int code); // +

size_t			ft_strlen(char const *str); // +
int				ft_atoi(char const *str); // +
long long int	get_time(void);
void			print_mutex(t_philo *philo, char *mess);

#endif