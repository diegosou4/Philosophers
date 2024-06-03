/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:24:40 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/29 18:19:07 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_atoil(const char *str)
{
	size_t	i;
	size_t	sign;
	size_t	result;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}

void	give_philo(t_philo *philo, t_table *table)
{
	static unsigned int	i;

	if (!philo)
		return ;
	philo->id = i + 1;
	i++;
	philo->count_meals = 0;
	philo->last_eat = 0;
	mutex_operation(&philo->my_mutex, INIT);
	philo->table = table;
}

int	parse_philo(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_isdigit(av[i]) == 1 || ft_atoi(av[i]) <= 0)
		{
			printf("Erro parse\n");
			exit(0);
		}
		i++;
	}
	return (1);
}
