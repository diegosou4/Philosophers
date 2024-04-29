/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:23:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/25 12:23:45 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/philo.h"

void philo_init(int ac,char **av)
{
    int i;
    i = 0;
    t_table *table;
    int len;

    len = ft_atoi(av[1]);
    if(len <= 0)
    {
        write(2, "Number Philo incorrent \n",25);
        exit(0);
    }
    table = malloc(sizeof(t_table) * 1);
    table->philo = malloc(sizeof(t_philo) * len);
    while(i < len)
    {
        give_philo(ac, av, &table->philo[i]);
        i++;
    }
    
    
}

void print_struct(t_table)
{


}