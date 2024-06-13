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
	free(table->philo);
	free(table);
}
int ft_strlen(char *av)
{
	int i;
	i = 0;

	while(av[i] != '\0')
	{
		i++;
	}
	return(i);
}