#include "../includes/philosophers.h"

static int	args_is_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i] && argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static long long int	ft_ll_atoi(char const *str)
{
	long long int	num;
	int				i;
	int				sign;

	sign = 1;
	i = 0;
	num = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

static int	check_int(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_ll_atoi(argv[i]) < -2147483648 || \
		ft_ll_atoi(argv[i]) > 2147483647)
			return (1);
		i++;
	}
	return (0);
}

int	validation_input_data(int argc, char **argv)
{
	if (args_is_digit(argc, argv))
		return (1);
	if (check_int(argc, argv))
		return (1);
	return (0);
}
