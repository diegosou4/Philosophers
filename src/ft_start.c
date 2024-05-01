/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:23:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/01 14:55:33 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

pthread_mutex_t *my_mutex(void)
{
    static pthread_mutex_t mutex;
    return(&mutex);
}

void rotine(t_philo *philo)
{
    pthread_mutex_lock(my_mutex());
    printf("%i id philo\n",philo->id);
    ft_usleep(philo->time_eat);
    pthread_mutex_unlock(my_mutex());
}

void philo_init(int ac,char **av)
{
    int i;
    i = 0;
    t_table *table;
    t_philo *ptr;
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
    ptr = table->philo;
    i = 0;
    pthread_mutex_init(my_mutex(), NULL);
    while (i < qtphilo)
    {
        pthread_create(&ptr[i].thread, NULL, (void *(*)(void *))rotine, &ptr[i]);
        i++;    
    }
    i = 0;
    while(i < qtphilo)
    {
        pthread_join(ptr[i].thread, NULL);
        i++;
    }
    // while(i < qtphilo)
    // {
    //     print_struct(&table->philo[i]);
    //     i++;
    // }
    
}

void print_struct(t_philo *philo)
{
    printf("%i id philo\n",philo->id);
    printf("time_eat %i \n", (int)philo->time_eat);
    printf("time_dead %i \n", (int)philo->time_dead);
    printf("time_sleep %i \n", (int)philo->time_sleep);
    printf("r_fork %i \n",philo->r_fork);
    // printf("l_fork %i \n",philo->l_fork);
    printf("x time %i \n",philo->xtime);
}