#include "../includes/philosophers.h"

int	write_error(char *mess)
{
	write(2, "Error: ", 7);
	write(2, mess, ft_strlen(mess));
	write(2, "\n", 1);
	return (1);
}

// int	manage_error()