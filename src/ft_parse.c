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
    philo->philo = ft_atoi(av[1]);
    philo->dead = ft_atoi(av[2]);
    philo->eat = ft_atoi(av[3]);
    philo->sleep = ft_atoi(av[4]);
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
        if(ft_isdigit(av[i]) == 1)
        {
            printf("Erro parse\n");
            exit(0);
        }

            i++;
    }
    return(1);
}