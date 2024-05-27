/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syncronize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:32:27 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/27 13:32:28 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


void thread_syncrinize(t_table *table)
{
    while (get_bool(&table->check,&table->sync) != true)
        ;
    
}
bool end_simulation(t_table *table)
{
    return(get_bool(&table->check,&table->is_dead));
}