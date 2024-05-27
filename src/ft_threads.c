/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:16:13 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/20 16:16:14 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"


void start_philo(t_table *table, int ac, char **av)
{
    int i;
    i = -1;
    table->philo = malloc(sizeof(t_philo) * table->qtphilo);
    while(++i < table->qtphilo)
         give_philo(ac, av, &table->philo[i],table);
}


void philo_operation(t_table *table, int flag)
{
    int i;
    i = -1; 
    t_philo *ptr;
    ptr = table->philo;
    if(flag == START)
    {
        while(++i < table->qtphilo)
        { 
            pthread_create(&ptr[i].thread, NULL, (void *(*)(void *))rotine, &ptr[i]);
        }
           set_bool(&table->num_lock,&table->sync,true);
        }
        else if(flag == WAIT)
        {
            while(++i < table->qtphilo)
                pthread_join(ptr[i].thread, NULL);
        }
}

bool thread_finish(t_philo *philo)
{
    bool res;
    int i;
 
    t_table *ptr;
    mutex_operation(&philo->table->num_lock,LOCK);
    ptr = philo->table;
    i = 0;
    while(i < philo->table->qtphilo)
    {
        if(ptr->philo[i].xtime != 0)
        {
            mutex_operation(&philo->table->num_lock,UNLOCK);
            return(false);
        }
        i++;
    }
    res = true;
    mutex_operation(&philo->table->num_lock,UNLOCK);
    return(res);
}