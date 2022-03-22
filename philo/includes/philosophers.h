#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKE_FORK "\033[1;34mhas taking a fork\033[0m"
# define EATING "\033[1;32mis eating\033[0m"
# define SLEEPING "\033[1;35mis sleeping\033[0m"
# define THINKING "is thinking"

# define ERROR_NUM_ARGS "Error: invalid number of arguments"
# define ERROR_INVALID_DATA "Error: invalid value of arguments"
# define ERROR_INIT_DATA "Error: init data"
# define ERROR_INIT_FORKS "Error: init forks"
# define ERROR_INIT_PHILOS "Error: init philosophers"

typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	int		id_fork;
	t_mutex	fork_mutex;
}				t_fork;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				death;
	long long int	start_program; // -
	t_mutex			stdout_mutex;
	t_fork			*forks;
}				t_data;

typedef struct s_philo
{
	int				id_philo;
	int				count_meals;
	long long int	last_eating; // -
	t_data			*data;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_mutex			condition_mutex;
	pthread_t		pid_pthread;
}				t_philo;

int		validation_input_data(int argc, char **argv);
int		init_data(t_data **data, int argc, char **argv);
int		init_philos(t_philo **philos, t_data *data);
int		init_forks(t_data *data);
void	*philo_life(void *args);

int		write_error(char *mess);
int		clear_data(t_data *data, t_philo *philos, char *mess_error);

size_t			ft_strlen(char const *str);
int				ft_atoi(char const *str);
long long int	get_time(void);
void			print_mutex(t_philo *philo, char *mess);

#endif