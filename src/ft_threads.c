/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:16:13 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/27 19:55:12 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

void give_forks(t_philo *philo)
{
    int mat; 
    mat = (philo->id + 1) % philo->table->qtphilo;
    if ((philo->id % 2) == 0) {
        philo->r_fork = &philo->my_mutex;
        philo->l_fork = &philo->table->philo[mat].my_mutex;
    } else {
        philo->l_fork = &philo->my_mutex;
        philo->r_fork = &philo->table->philo[mat].my_mutex;
    }
}

void start_philo(t_table *table, int ac, char **av)
{
    int i;
    i = -1;
    if(ac == 6)
        table->xtime = ft_atoi(av[5]);
    else
        table->xtime = -1;
    table->philo = malloc(sizeof(t_philo) * table->qtphilo);
    while(++i < table->qtphilo)
         give_philo(ac, av, &table->philo[i],table);
    i = -1;
    while(++i < table->qtphilo)
    {   
        give_forks(&table->philo[i]);
    }
}


void philo_operation(t_table *table)
{
    int i;
    i = -1; 
    t_philo *ptr;
    ptr = table->philo;
    if(table->xtime == 0)
        return;
    else if(table->qtphilo == 1)
        return;
    else{
         while(++i < table->qtphilo)
            pthread_create(&ptr[i].thread, NULL, (void *(*)(void *))rotine, &ptr[i]);
    }
    pthread_create(&table->main, NULL, (void *(*)(void *))main_rotine, table);
    table->start_time = get_current_time();
    set_bool(&table->check,&table->sync,true);
    i = -1;
    while(++i < table->qtphilo)
            pthread_join(ptr[i].thread, NULL);
    set_bool(&table->num_lock,&table->end,true);
    pthread_join(table->main, NULL);
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