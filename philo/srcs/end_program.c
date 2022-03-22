#include "../includes/philosophers.h"

int	write_error(char *mess)
{
	write(1, mess, ft_strlen(mess));
	write(1, "\n", 1);
	return (1);
}

int	clear_data(t_data *data, t_philo *philos, char *mess_error)
{
	if (data)
	{
		if (data->forks)
			free (data->forks);
		free (data);
	}
	if (philos)
		free (philos);
	if (mess_error)
		return (write_error(mess_error));
	else
		return (0);
}