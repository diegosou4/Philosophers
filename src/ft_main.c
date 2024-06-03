/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:24:46 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/27 19:52:43 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	last_eat(t_philo *philo, t_table *table)
{
	size_t	timenow;
	size_t	last;

	if(get_bool(&table->dead_lock,&philo->is_full) == true)
		return(false);
	last = table->time_dead;
	timenow = time_diff(philo->table->start_time)
		- get_long(&philo->table->dead_lock, &philo->last_eat);
	if (timenow > last)
		return (true);
	return (false);
}

bool	dead_all_philos(t_table *table)
{
	int	i;
	int meals;
	meals = 0;
	i = -1;
	while (++i < table->qtphilo)
	{
		pthread_mutex_lock(&table->dead_lock);
		meals = table->philo[i].count_meals;
		pthread_mutex_unlock(&table->dead_lock);
		if (meals < table->max_meals)
			return (false);
	}
	return (true);
}

void	main_rotine(t_table *table)
{
	int	i;

	thread_syncrinize(table);
	while (!end_simulation(table))
	{
		if(table->max_meals != -1)
		{
		if (dead_all_philos(table) == true)
		{
			set_bool(&table->dead_lock, &table->end, true);
			return ;
		}
		}
		i = -1;
		while (++i < table->qtphilo && !end_simulation(table))
		{
			if (last_eat(table->philo + i, table) == true)
			{
				set_bool(&table->dead_lock, &table->end, true);
				print_status(table->philo + i, DEAD);
				return ;
			}
		}
	}
}
