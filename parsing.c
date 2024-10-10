#include "philo.h"

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		i++;
	}
	return (i);
}

int is_valid_str(char *str)
{
	int i;
	int space;

	i = 0;
	space = 0;

	while(str[i])
	{
		if((str[i] && str[i] >= '0' && str[i] <= '9'))
			i++;
		else if(str[i] == ' ')
		{
			i++;
			space++;
		}
		else
			return (0);
	}
	if(ft_strlen(str) == space)
		return (0);
	return (1);
}

int ft_atoi(char *str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while(str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}