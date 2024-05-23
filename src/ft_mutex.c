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
    mutex_operation(&table->num_lock, flag);
    

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

void del_mutex_philo(t_philo *philo, int qtphilo)
{
    int i;
    i = 0;
    while(i < qtphilo)
    {
        mutex_operation(&philo[i].my_mutex, DESTROY);
        i++;
    }
}