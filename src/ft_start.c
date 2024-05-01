/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:23:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/01 10:39:13 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

void philo_init(int ac,char **av)
{
    int i;
    i = 0;
    t_table *table;
    int qtphilo;

    qtphilo = ft_atoi(av[1]);
    if(qtphilo <= 0)
    {
        write(2, "Number Philo incorrent \n",25);
        exit(0);
    }
    table = malloc(sizeof(t_table) * 1);
    table->philo = malloc(sizeof(t_philo) * qtphilo);
    while(i < qtphilo)
    {
        give_philo(ac, av, &table->philo[i]);
        i++;
    }
    i = 0;
    while(i < qtphilo)
    {
        print_struct(&table->philo[i]);
        i++;
    }
    
}

void print_struct(t_philo *philo)
{
    printf("%i id philo\n",philo->id);
    printf("time_eat %i \n", (int)philo->time_eat);
    printf("time_dead %i \n", (int)philo->time_dead);
    printf("time_sleep %i \n", (int)philo->time_sleep);
    printf("r_fork %i \n",philo->r_fork);
    printf("l_fork %i \n",philo->l_fork);
    printf("x time %i \n",philo->xtime);
}