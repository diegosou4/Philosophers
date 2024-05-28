/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:24:46 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/27 19:52:43 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

bool last_eat(t_philo *philo, t_table *table) 
{
    int i;
    long timenow;
    long last;

    last = get_long(&philo->table->dead_lock, &philo->time_dead);
    timenow = time_diff(philo->table->start_time) - get_long(&philo->table->dead_lock, &philo->last_eat);   
    if (timenow > last) 
    {
        set_bool(&table->dead_lock,&table->end,true);
        set_long(&table->dead_lock,&philo->time_dead,timenow);
        mutex_operation(&table->dead_lock,LOCK);
        philo->table->id_dead = philo->id;
        mutex_operation(&table->dead_lock,UNLOCK);
        print_status(philo,DEAD);
        return (true);
    }
    return(false);
}

bool last_time(t_table *table)
{
    bool died;
    int i;
    i = -1;
    died = false;
    mutex_operation(&table->check,LOCK);
    while(++i < table->qtphilo)
    {
        if(last_eat(&table->philo[i],table) == true)
        {
            died = true;
            break;
        }  
    }
    mutex_operation(&table->check,UNLOCK);
    return(died);
}

bool is_died(t_table *table)
{
    int i;
    i = -1;
    bool died;

    if(get_bool(&table->dead_lock,&table->end) == true)
        return(true);
    if(last_time(table) == true)
        return(true);
    mutex_operation(&table->check,LOCK);
    died = true;
    while(++i < table->qtphilo)
    {   
        if(table->philo[i].is_full != true)
        {
            died = false;
            break;
        }
    }
    mutex_operation(&table->check,UNLOCK);
    set_bool(&table->check,&table->is_dead,died);
    return(died);
}


void main_rotine(t_table *table)
{

    int i;
    i = 0;
    thread_syncrinize(table);
    while(is_died(table) != true)
        ;
}

