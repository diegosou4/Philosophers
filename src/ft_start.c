/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:23:44 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/27 19:58:59 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

void print_status(t_philo *philo, int status)
{
    mutex_operation(&philo->table->printf_lock, LOCK);
    if(status == TAKE) 
        printf("%zu %d has taken a fork\n",time_diff(philo->table->start_time),philo->id);
    else if(status == EAT)
        printf("%zu %d is eating\n",time_diff(philo->table->start_time),philo->id);
    else if(status == SLEEP)
        printf("%zu %d is sleeping\n",time_diff(philo->table->start_time),philo->id);
    else if(status == DEAD )
        printf("%zu %d died\n",philo->time_dead,philo->id);
    mutex_operation(&philo->table->printf_lock, UNLOCK);
}

void take_fork(t_philo *philo) {
    int mat = (philo->id + 1) % philo->table->qtphilo;

    if ((philo->id % 2) == 0) {
        philo->r_fork = &philo->my_mutex;
        philo->l_fork = &philo->table->philo[mat].my_mutex;
    } else {
        philo->l_fork = &philo->my_mutex;
        philo->r_fork = &philo->table->philo[mat].my_mutex;
    }
    mutex_operation(philo->l_fork, LOCK);
    if (end_simulation(philo->table) == true) 
    {
        mutex_operation(philo->l_fork, UNLOCK);
        return;
    } else 
         print_status(philo, TAKE);
    mutex_operation(philo->r_fork, LOCK);
    if (end_simulation(philo->table) == true) {
        mutex_operation(philo->l_fork, UNLOCK);  
        mutex_operation(philo->r_fork, UNLOCK);
        return;
    } else {
        print_status(philo, TAKE);
    }
}

      

void eat(t_philo *philo)
{
    if(end_simulation(philo->table) != true)
    {
        set_long(&philo->table->dead_lock,&philo->last_eat,time_diff(philo->table->start_time));
        print_status(philo,EAT);
        ft_usleep(philo->time_eat);
        mutex_operation(philo->l_fork, UNLOCK);
        mutex_operation(philo->r_fork, UNLOCK);
        mutex_operation(&philo->table->num_lock,LOCK);
        philo->count_meals++;
        if(philo->count_meals == philo->xtime && philo->xtime > 0)
            set_bool(&philo->table->dead_lock,&philo->is_full,true);
        mutex_operation(&philo->table->num_lock,UNLOCK);
    }
   
}
void sleep_philo(t_philo *philo)
{
    if(end_simulation(philo->table) != true)
    {
        print_status(philo,SLEEP);
        ft_usleep(philo->time_sleep);
    }
}
void thinking(t_philo *philo)
{
    if(end_simulation(philo->table) != true)
        printf("%zu %d is thinking\n",time_diff(philo->table->start_time),philo->id);
}


void rotine(t_philo *philo) 
{ 
    thread_syncrinize(philo->table);
    while (end_simulation(philo->table) == false) 
    {
        if(get_bool(&philo->table->dead_lock,&philo->is_full) == true)
            return;
            take_fork(philo);
            eat(philo);
            sleep_philo(philo);
            thinking(philo);
    }
    
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
    table->is_dead = false;
    table->end = false;
    table->sync = false;
    mutex_table_operation(table,INIT);
    start_philo(table,ac,av);
    philo_operation(table);
    del_mutex_philo(table->philo,qtphilo);
    mutex_table_operation(table,DESTROY);
}
