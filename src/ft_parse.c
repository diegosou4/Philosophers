/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:24:40 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/01 14:41:35 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"


void give_philo(int ac,char **av, t_philo *philo)
{
    static unsigned int i;
    
    if(!philo)
        return;
    philo->id = i;
   
    i++;
    philo->time_dead = ft_atoi(av[2]);
    philo->time_eat = ft_atoi(av[3]);
    philo->time_sleep = ft_atoi(av[4]);
    mutex_operation(&philo->my_mutex, INIT);
    // philo->r_fork = 1;
    if(ac == 6)
        philo->xtime = ft_atoi(av[5]);
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
