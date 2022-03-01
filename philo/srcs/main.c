#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_fork			forks[200];
	t_philosopher	philos[200];
	t_data			data;
	int		error;

	if (argc < 5 || argc > 6)
		return (write_error(ERROR_NUM_ARGS));
	// if (validation_input_data(argc, argv))
	// 	return (write_error(ERROR_VALIDATION_ARGS));
	if (init_data(argc, argv, &data));
		return (write_error("Error init data"));
	if (init_forks(forks, &data))
		return (write_error("Error init forks"));
	if (init_philosopher(philos, &data, forks))
		return (write_error("Error init philosophers"));
	return (0);
}