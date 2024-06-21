/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <diegmore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:23:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/06/21 09:55:10 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->table->printf_lock);
	if (status == TAKE && !end_simulation(philo->table))
		printf("%zu %d has taken a fork\n", time_diff(philo->table->start_time),
			philo->id);
	else if (status == EAT && !end_simulation(philo->table))
		printf("%zu %d is eating\n", time_diff(philo->table->start_time),
			philo->id);
	else if (status == SLEEP && !end_simulation(philo->table))
		printf("%zu %d is sleeping\n", time_diff(philo->table->start_time),
			philo->id);
	else if (status == THINK && !end_simulation(philo->table))
		printf("%zu %d is thinking\n", time_diff(philo->table->start_time),
			philo->id);
	else if (status == DEAD && end_simulation(philo->table) == true)
		printf("%zu %d died\n", time_diff(philo->table->start_time), philo->id);
	pthread_mutex_unlock(&philo->table->printf_lock);
}

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, TAKE);
	print_status(philo, TAKE);
}

void	eat(t_philo *philo, t_table *table)
{
	if (!end_simulation(philo->table))
	{
		take_fork(philo);
		set_long(&table->dead_lock, &philo->last_eat,
			time_diff(table->start_time));
		print_status(philo, EAT);
		ft_usleep(table->time_eat, philo->table);
		pthread_mutex_lock(&table->dead_lock);
		philo->count_meals++;
		pthread_mutex_unlock(&table->dead_lock);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
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
	size_t	t_think;

	if (end_simulation(philo->table) == false)
	{
		print_status(philo, THINK);
		if(philo->table->qtphilo % 2 == 0)
			return;
		t_think = (philo->table->time_eat * 2) - philo->table->time_sleep;
		if(t_think < 0)
			t_think = 0;
		ft_usleep(t_think, philo->table);
	}
}
