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
    size_t timenow;
    size_t last;

    last = table->time_dead;
    timenow = time_diff(philo->table->start_time) - get_long(&philo->table->dead_lock, &philo->last_eat);   
    if (timenow > last) 
        return (true);
    return(false);
}


void main_rotine(t_table *table)
{

    int i;
    
    thread_syncrinize(table);
    while(!end_simulation(table))
    {
        i = -1;
        while(++i < table->qtphilo && !end_simulation(table))
        {
            if(last_eat(table->philo + i,table) == true)
            {
                set_bool(&table->check,&table->end,true);
                print_status(table->philo + i, DEAD);
            }
        }
    }
   
}

