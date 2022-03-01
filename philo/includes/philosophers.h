#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# define ERROR_NUM_ARGS "Invalid number of arguments"
# define ERROR_VALIDATION_ARGS "Invalid input arguments"

typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	int		id_fork;
	int		is_busy;
	t_mutex	mutex;
}				t_fork;


typedef struct s_philosopher
{
	int				id_philo;
	int				num_eating;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_mutex			*stdout_mutex;
	t_mutex			condition_philo;
	long long int	last_eating;
	int				time_to_eat;
	int				time_to_sleep;

}				t_philosopher;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eating;
	t_mutex			stdout_mutex;
	long long int	begin_program;
}				t_data;

int		init_data(int argc, char **argv, t_data *data);

size_t	ft_strlen(char const *str);
int		ft_atoi(char const *str);


#endif