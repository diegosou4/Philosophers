/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:23:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/29 18:27:32 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, int status)
{
	mutex_operation(&philo->table->printf_lock, LOCK);
	if (status == TAKE && !end_simulation(philo->table))
		printf("%zu %d has taken a fork\n", time_diff(philo->table->start_time),
			philo->id);
	else if (status == EAT && !end_simulation(philo->table))
		printf("%zu %d is eating\n", time_diff(philo->table->start_time),
			philo->id);
	else if (status == SLEEP && !end_simulation(philo->table))
		printf("%zu %d is sleeping\n", time_diff(philo->table->start_time),
			philo->id);
	else if (status == DEAD && end_simulation(philo->table) == true)
		printf("%zu %d died\n", time_diff(philo->table->start_time), philo->id);
	mutex_operation(&philo->table->printf_lock, UNLOCK);
}

bool	take_fork(t_philo *philo)
{
	if (!end_simulation(philo->table))
		mutex_operation(philo->l_fork, LOCK);
	if (!end_simulation(philo->table))
	{
		mutex_operation(philo->r_fork, LOCK);
		print_status(philo, TAKE);
		print_status(philo, TAKE);
		return (true);
	}
	else
	{
		mutex_operation(philo->l_fork, UNLOCK);
	}
	return (false);
}

void	eat(t_philo *philo, t_table *table)
{
	bool	done;

	done = take_fork(philo);
	if (!end_simulation(philo->table))
	{
		if (done == true)
		{
			set_long(&table->dead_lock, &philo->last_eat,
				time_diff(table->start_time));
			print_status(philo, EAT);
			ft_usleep(table->time_eat, philo->table);
			mutex_operation(&philo->table->dead_lock, LOCK);
			philo->count_meals++;
			mutex_operation(&philo->table->dead_lock, UNLOCK);
			if (philo->count_meals == table->max_meals 
				&& table->max_meals != -1)
				set_bool(&philo->table->dead_lock, &philo->is_full, true);
		}
	}
	if (done == true)
	{
		mutex_operation(philo->l_fork, UNLOCK);
		mutex_operation(philo->r_fork, UNLOCK);
	}
}

void	sleep_philo(t_philo *philo, t_table *table)
{
	if (!end_simulation(philo->table))
	{
		print_status(philo, SLEEP);
		ft_usleep(table->time_sleep, table);
	}
}

void	thinking(t_philo *philo)
{
	if (!end_simulation(philo->table))
		printf("%zu %d is thinking\n", time_diff(philo->table->start_time),
			philo->id);
}
