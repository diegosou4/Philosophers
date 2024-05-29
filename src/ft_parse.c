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
    philo->id = i;
    i++;
    philo->status = LIVE;
    philo->count_meals = 0;
    philo->last_eat = 0;
    philo->is_full = false;
    mutex_operation(&philo->my_mutex, INIT);
    philo->table = table;
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
