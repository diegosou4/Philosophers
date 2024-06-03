/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:22:36 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/23 14:56:04 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	philo_init(int ac, char **av)
{
	t_table	*table;
	int		qtphilo;

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
	mutex_table_operation(table, INIT);
	start_philo(table, ac, av);
	philo_operation(table);
	del_mutex_philo(table);
	mutex_table_operation(table, DESTROY);
	free_philo(table);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (parse_philo(ac, av) == 1)
		{
			philo_init(ac, av);
		}
	}
	else
	{
		printf("Number Arguments Incorret!!\n");
	}
	return (0);
}
