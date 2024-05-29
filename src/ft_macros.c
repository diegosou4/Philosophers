/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_macros.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:45:51 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/29 18:16:54 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	get_bool(pthread_mutex_t *mutex, bool *is_dead)
{
	bool	get;

	mutex_operation(mutex, LOCK);
	get = *is_dead;
	mutex_operation(mutex, UNLOCK);
	return (get);
}

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	mutex_operation(mutex, LOCK);
	*dest = value;
	mutex_operation(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, size_t *value)
{
	long	tmp;

	mutex_operation(mutex, LOCK);
	tmp = *value;
	mutex_operation(mutex, UNLOCK);
	return (tmp);
}

void	set_long(pthread_mutex_t *mutex, size_t *dest, long value)
{
	mutex_operation(mutex, LOCK);
	*dest = value;
	mutex_operation(mutex, UNLOCK);
}
