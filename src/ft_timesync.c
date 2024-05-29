/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_timesync.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:32:27 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/29 18:29:28 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	thread_syncrinize(t_table *table)
{
	while (get_bool(&table->check, &table->sync) != true)
		;
}

bool	end_simulation(t_table *table)
{
	return (get_bool(&table->check, &table->end));
}

int	ft_usleep(size_t milliseconds, t_table *table)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (end_simulation(table) == true)
			break ;
		usleep(100);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	time_diff(size_t time)
{
	return (get_current_time() - time);
}
