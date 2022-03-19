#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	// t_fork			forks[200];
	// t_philosopher	philos[200];
	t_data			data;
	// int		error;

	if (argc < 5 || argc > 6)
		return (write_error(ERROR_NUM_ARGS));
	// if (validation_input_data(argc, argv))
	// 	return (write_error(ERROR_VALIDATION_ARGS));
	if (init_data(argc, argv, &data))
		return (write_error("Error init data"));
	if (init_forks(&data))
		return (write_error("Error init forks"));
	// if (init_philosopher(philos, &data, forks))
	// 	return (write_error("Error init philosophers"));

	printf("num_philos = %d\n", data.num_philos);
	printf("time_to_die = %d\n", data.time_to_die);
	printf("time_to_eat = %d\n", data.time_to_eat);
	printf("time_to_sleep = %d\n", data.time_to_sleep);

	return (0);
}