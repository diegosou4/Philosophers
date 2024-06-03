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
	else if(status == THINK && !end_simulation(philo->table))
		printf("%zu %d is thinking\n",time_diff(philo->table->start_time),philo->id);
	else if (status == DEAD && end_simulation(philo->table) == true)
		printf("%zu %d died\n", time_diff(philo->table->start_time), philo->id);
	mutex_operation(&philo->table->printf_lock, UNLOCK);
}

void	take_fork(t_philo *philo)
{
		if(philo->id % 2 == 0)
		{
			mutex_operation(philo->r_fork, LOCK);
			mutex_operation(philo->l_fork, LOCK);
		}else{
			mutex_operation(philo->l_fork, LOCK);
			mutex_operation(philo->r_fork, LOCK);
		}
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
		mutex_operation(&philo->table->dead_lock, LOCK);
		philo->count_meals++;
		mutex_operation(&philo->table->dead_lock, UNLOCK);
	}
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
}
		

void	sleep_philo(t_philo *philo, t_table *table)
{
		print_status(philo, SLEEP);
		ft_usleep(table->time_sleep, table);
}

void	thinking(t_philo *philo)
{
		size_t t_think;
		
		t_think = (philo->table->time_eat * 2) - philo->table->time_sleep;
		print_status(philo, THINK);
		usleep(t_think);
}
