/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:24:40 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/23 16:24:41 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"



t_philo *give_philo(int ac,char **av)
{
    t_philo *philo;

    philo = (t_philo *)malloc(sizeof(t_philo) * 1);
    if(!philo)
        return(NULL);
    philo->time_dead = ft_atoi(av[2]);
    philo->time_eat = ft_atoi(av[3]);
    philo->time_sleep = ft_atoi(av[4]);
    if(ac == 6)
        philo->xtime = ft_atoi(av[5]);
    else
        philo->xtime = -1;
    return(philo);
}
void create_table(int ac,char *av)
{
    t_table *table;
    int i;
    i = 0;
    table = malloc(sizeof(t_table) * 1);
    if(!table)
        return;
    while(i < ft_atoi(av[1]))
    {
        
    }

}

int parse_philo(int ac,char **av)
{   
    int i;
    i = 1;
    while(i < ac)
    {
        if(ft_isdigit(av[i]) == 1)
        {
            printf("Erro parse\n");
            exit(0);
        }

            i++;
    }
    return(1);
}