/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:31:58 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/22 13:31:59 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



void monitor(t_table *table)
{
    t_philo *ptr;

    ptr = &table->philo[table->id_dead];
    int i;
    i = 0;
   while(table->is_dead != true)
        ;
    if(table->is_dead == true)
    {
        print_status(ptr,DEAD);
        exit(0);
    }
}

void start_monitor(t_table *table, int flag)
{
    int i;
    i = -1; 

    if(flag == START)
    {
        pthread_create(&table->monitor,NULL, (void *(*)(void *))monitor, (void *)table);
    }
    else if(flag == WAIT)
    {
        pthread_join(table->monitor,NULL);
    }
}   