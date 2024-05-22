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

static bool philo_died(t_philo *philo)
{
    long elapsed;
    long time_td;

    if(get_bool(&philo->table->dead_lock,&philo->is_full) == true)  
        return(true);
    return(false);
    // elapsed = get_current_time() - get_long(&philo->table->num_lock,&philo->last_eat);
    // time_td = philo->time_dead;
    // if(elapsed > time_td)
    //     return(true);
    // else
    //     return(false);

}

void print_status(t_philo *philo, int status)
{
    mutex_operation(&philo->table->printf_lock, LOCK);
    if(status == TAKE && philo->table->is_dead != true)
        printf("%zu %d has taken a fork\n",time_diff(philo->table->start_time),philo->id);
    else if(status == EAT && philo->table->is_dead != true)
        printf("%zu %d is eating\n",time_diff(philo->table->start_time),philo->id);
    else if(status == SLEEP && philo->table->is_dead != true)
        printf("%zu %d is sleeping\n",time_diff(philo->table->start_time),philo->id);
    else if(status == DEAD )
        printf("%zu %d died\n",time_diff(philo->table->start_time),philo->id);
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
    print_status(philo,TAKE);
    mutex_operation(philo->r_fork, LOCK);
    print_status(philo,TAKE);
}

void eat(t_philo *philo)
{
    if(philo->xtime == 0 && thread_finish(philo) == true)
    {
        mutex_operation(&philo->table->num_lock,LOCK);
        philo->is_full = true;
        philo->table->is_dead = true;
        philo->table->id_dead = philo->id;
        mutex_operation(&philo->table->num_lock,UNLOCK);
    } 
    set_long(&philo->table->num_lock,&philo->last_eat,time_diff(philo->table->start_time));
    mutex_operation(&philo->table->num_lock,LOCK);
    philo->xtime--;
    mutex_operation(&philo->table->num_lock,UNLOCK);
    print_status(philo,EAT);
    ft_usleep(philo->time_eat);
    mutex_operation(philo->l_fork, UNLOCK);
    mutex_operation(philo->r_fork, UNLOCK);
}
void sleep_philo(t_philo *philo)
{
    if(get_bool(&philo->table->num_lock,&philo->table->is_dead) != true)
    {
        print_status(philo,SLEEP);
        ft_usleep(philo->time_sleep);
    }else
        return;
 
}
void thinking(t_philo *philo)
{
    if(get_bool(&philo->table->num_lock,&philo->table->is_dead) != true)
        printf("%zu %d is thinking\n",time_diff(philo->table->start_time),philo->id);
    else
        return;
}

void rotine(t_philo *philo) 
{    

    philo->table->start_time = get_current_time();
   
    while (get_bool(&philo->table->num_lock,&philo->table->is_dead) != true) 
    {
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
    mutex_table_operation(table,INIT);
    start_philo(table,ac,av);
    start_monitor(table,START);
    philo_operation(table,START);
     start_monitor(table, WAIT);
    philo_operation(table,WAIT);
   
    del_mutex_philo(table->philo,qtphilo);
    mutex_table_operation(table,DESTROY);
}
