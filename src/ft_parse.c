/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:24:40 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/27 19:47:56 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"


void give_philo(int ac,char **av, t_philo *philo,t_table *table)
{
    static unsigned int i;
    int x;
    if(!philo)
        return;
    mutex_operation(&table->num_lock,LOCK);
    philo->id = i;
    i++;
    mutex_operation(&table->num_lock, UNLOCK);
    philo->status = LIVE;
    philo->time_dead = ft_atoi(av[2]);
    philo->time_eat = ft_atoi(av[3]);
    philo->time_sleep = ft_atoi(av[4]);
    philo->last_eat = get_current_time();
    philo->is_full = false;
    mutex_operation(&philo->my_mutex, INIT);
    philo->table = table;
    if(ac == 6)
    {
         philo->xtime = ft_atoi(av[5]);
    }
       
    else
        philo->xtime = -1;
}
int parse_philo(int ac,char **av)
{   
    int i;
    i = 1;
    while(i < ac)
    {
        if(ft_isdigit(av[i]) == 1 || ft_atoi(av[i]) <= 0)
        {
            printf("Erro parse\n");
            exit(0);
        }
        i++;
    }   
    return(1);
}
