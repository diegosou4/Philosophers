/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:23:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/16 22:43:27 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

void print_status(t_philo *philo, int status)
{
    mutex_operation(&philo->table->printf_lock, LOCK);
    if(status == TAKE )
        printf("%zu %d has taken a fork\n",time_diff(philo->table->start_time),philo->id);
    else if(status == EAT)
        printf("%zu %d is eating\n",time_diff(philo->table->start_time),philo->id);
    else if(status == SLEEP)
        printf("%zu %d is sleeping\n",time_diff(philo->table->start_time),philo->id);
    else if(status == DEAD)
        printf("%zu %d is dead\n",time_diff(philo->table->start_time),philo->id);
    mutex_operation(&philo->table->printf_lock, UNLOCK);
}

void take_fork(t_philo *philo)
{
    int mat;
    mat = 0;

    mat = (philo->id + 1) % philo->table->qtphilo;
    if((philo->id % 2) == 0)
    {
        philo->r_fork = &philo->my_mutex;
        philo->l_fork = &philo->table->philo[mat].my_mutex;
    }else{
        philo->l_fork = &philo->my_mutex;
        philo->r_fork = &philo->table->philo[mat].my_mutex;
    }
    mutex_operation(philo->l_fork, LOCK);
    mutex_operation(philo->r_fork, LOCK);
    print_status(philo,TAKE);
    print_status(philo,TAKE);
}

void eat(t_philo *philo)
{
    if(philo->xtime == 0)
    {
        philo->table->is_dead = true;
        philo->table->id_dead = philo->id;
    }else
    {
        philo->xtime--;
        print_status(philo,EAT);
        ft_usleep(philo->time_eat);
    }
    mutex_operation(philo->l_fork, UNLOCK);
    mutex_operation(philo->r_fork, UNLOCK);
}
void sleep_philo(t_philo *philo)
{
    print_status(philo,SLEEP);
    ft_usleep(philo->time_sleep);
}
void thinking(t_philo *philo)
{
    printf("%zu %d is thinking\n",time_diff(philo->table->start_time),philo->id);
}

void rotine(t_philo *philo) 
{    

    philo->table->start_time = get_current_time();
    start_monitor(philo->table,INIT);
    while (1) 
    {
        take_fork(philo);
        eat(philo);
        sleep_philo(philo);
        thinking(philo);
    }
    start_monitor(philo->table, WAIT);
}

void philo_init(int ac, char **av)
{
    int i;
    t_table *table;
    t_philo *ptr;
    int qtphilo;  
    qtphilo = ft_atoi(av[1]);
    if (qtphilo <= 0)
    {
        write(2, "Number Philo incorrent \n", 25);
        exit(0);
    }
    table = malloc(sizeof(t_table));
    table->qtphilo = qtphilo;
    table->num = 0;
    mutex_table_operation(table,INIT);
    start_philo(table,ac,av);
    
    philo_operation(table,START);
    philo_operation(table,WAIT);
    del_mutex_philo(table->philo,qtphilo);
    mutex_table_operation(table,DESTROY);
}
