/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:24:40 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/27 19:47:56 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

int	ft_isdigit(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if(!(str[i] >= '0' && str[i] <= '9') && str[i] != '+')
			return(1);
		i++;
	}
	return (0);
}

size_t	ft_atoi(const char *str)
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

void give_philo(t_philo *philo,t_table *table)
{
    static unsigned int i;
    if(!philo)
        return;
    philo->id = i;
    i++;
    philo->count_meals = 0;
    philo->last_eat = 0;
    philo->is_full = false;
    mutex_operation(&philo->my_mutex, INIT);
    philo->table = table;
}

int parse_philo(int ac,char **av)
{   
    int i;
    i = 1;
    while(i < ac)
    {
        if(ft_isdigit(av[i]) == 1 || ft_atoi(av[i]) <= 0)
        {
            printf("Erro parse\n");
            exit(0);
        }
        i++;
    }   
    return(1);
}

void philo_init(int ac, char **av)
{
    t_table *table;
    int qtphilo;  
    qtphilo = ft_atoi(av[1]);
    if (qtphilo <= 0)
    {
        write(2, "Number Philo incorrent \n", 25);
        exit(0);
    }
    table = malloc(sizeof(t_table));
    table->qtphilo = qtphilo;
    table->is_dead = false;
    table->end = false;
    table->sync = false;
    mutex_table_operation(table,INIT);
    start_philo(table,ac,av);
    philo_operation(table);
    del_mutex_philo(table);
    mutex_table_operation(table,DESTROY);
}