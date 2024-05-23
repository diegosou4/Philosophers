/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:24:46 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/23 12:24:47 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

bool last_eat(t_philo *philo) 
{
    int i;
    long timenow;
    long last;

    last = get_long(&philo->table->dead_lock, &philo->time_dead);
    timenow = time_diff(philo->table->start_time) - get_long(&philo->table->dead_lock, &philo->last_eat);    
    if (timenow > last + 10) 
    {
        printf("%zu \n", timenow);
        printf("died because the time\n");
        exit(0);
        return true;
    }
    return(false);
}

bool is_died(t_table *table)
{
    bool died;
    int i;
    mutex_operation(&table->num_lock, LOCK);
    i = 0;
    died = true;
    while(i < table->qtphilo)
    {   
        if(table->philo[i].xtime != 0 || last_eat(&table->philo[i]) != false)
        {
            died = false;
            break;
        }
        i++;
    }
    mutex_operation(&table->num_lock, UNLOCK);
    return(died);
}


void main_rotine(t_table *table)
{

    int i;
    i = 0;
    while(is_died(table) != true)
        ;
    if(is_died(table) == true)
    {
        mutex_operation(&table->printf_lock,LOCK);
        printf("%zu %d died x time\n",time_diff(table->start_time),table->is_dead);
        mutex_operation(&table->printf_lock,UNLOCK);
        exit(0);
    }

}


void main_operation(t_table *table, int flag)
{
    if(flag ==  START)
    {
        pthread_create(&table->main, NULL, (void *(*)(void *))main_rotine, table);
    }
        
    else if(flag == WAIT)
        pthread_join(table->main,NULL);
}