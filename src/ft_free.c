/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:12:52 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/29 18:12:53 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->qtphilo)
	{
		free(&table->philo[i]);
	}
	free(table);
}
