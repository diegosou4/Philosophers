/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:57:55 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/20 15:57:56 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"


void mutex_table_operation(t_table *table,int flag)
{
    mutex_operation(&table->dead_lock, flag);
    mutex_operation(&table->printf_lock,flag);
    mutex_operation(&table->check,flag);

}

void mutex_operation(pthread_mutex_t *mutex, int flag)
{
    if(flag == INIT)
        pthread_mutex_init(mutex,NULL);
    else if(flag == DESTROY)
        pthread_mutex_destroy(mutex);
    else if(flag == LOCK)
        pthread_mutex_lock(mutex);
    else if(flag == UNLOCK)
        pthread_mutex_unlock(mutex);
}

void del_mutex_philo(t_table *table)
{
    int i;
    i = -1;
    while(++i < table->qtphilo)
    {
        mutex_operation(&table->philo[i].my_mutex, DESTROY);
    }
}