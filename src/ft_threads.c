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
        table->max_meals = ft_atoi(av[5]);
    else
        table->max_meals = -1;
    table->philo = malloc(sizeof(t_philo) * table->qtphilo);
    table->time_dead = ft_atoi(av[2]);
    table->time_eat = ft_atoi(av[3]);
    table->time_sleep = ft_atoi(av[4]);
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
    if(table->max_meals == 0)
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
    set_bool(&table->check,&table->end,true);
    pthread_join(table->main, NULL);
}
