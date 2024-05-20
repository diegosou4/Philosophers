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

pthread_mutex_t *mutexes;

pthread_mutex_t *my_mutex(void)
{
    static pthread_mutex_t mutex;
    return(&mutex);
}
void take_fork(t_table *table , int id)
{
    table->philo[id].r_fork = &table->philo[id].my_mutex;
    table->philo[id].l_fork = &table->philo[(id + 1) % table->qtphilo].my_mutex; 
    if(table->philo[id].id % 2 == 0)
    {
        table->philo[id].l_fork = &table->philo[id].my_mutex;
        table->philo[id].r_fork = &table->philo[(id + 1) % table->qtphilo].my_mutex; // Evita acesso fora do limite
    }
    pthread_mutex_lock(table->philo[id].l_fork);
    pthread_mutex_lock(table->philo[id].r_fork);
    printf("%zu %d has taken a fork\n",time_diff(table->start_time),table->philo[id].id);
}
void eat(t_table *table, int id)
{
    pthread_mutex_lock(&table->dead_eat);
    printf("%zu %d is eating\n",time_diff(table->start_time),table->philo[id].id);
    ft_usleep(table->philo[id].time_eat);
    table->philo[id].xtime--;
    pthread_mutex_unlock(&table->dead_eat);
    pthread_mutex_unlock(table->philo[id].l_fork);
    pthread_mutex_unlock(table->philo[id].r_fork);
}

void sleep_philo(t_table *table, int id)
{
    pthread_mutex_lock(&table->dead_sleep);
    printf("%zu %d is sleeping\n",time_diff(table->start_time),table->philo[id].id);
    ft_usleep(table->philo[id].time_sleep);
    pthread_mutex_unlock(&table->dead_sleep);
}

void thinking(t_table *table, int id)
{
    size_t time;
    time = get_current_time();
    pthread_mutex_lock(&table->thinking);
    printf("%zu %d is thinking\n",time_diff(table->start_time),table->philo[id].id);
    pthread_mutex_unlock(&table->thinking);
}

void rotine(t_table *table) 
{    
    int id;
    int qtphilo = table->qtphilo;
    pthread_mutex_lock(&table->num_lock);
    if(id == table->qtphilo)
        id = 0;
    else if(id != table->qtphilo && id != -1)
        id = table->num++;
    pthread_mutex_unlock(&table->num_lock);
    table->start_time = get_current_time();
    while (1 && table->philo[id].xtime  > 0 || table->philo[id].xtime == -1) 
    {
        take_fork(table,id);
        eat(table,id);
        sleep_philo(table,id);
        thinking(table,id);
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
    start_philo(table,ac,av);
    mutex_table_operation(table,INIT);
    philo_operation(table,START);
    philo_operation(table,WAIT);
    del_mutex_philo(table->philo,qtphilo);
    mutex_table_operation(table,DESTROY);
}






// void print_struct(t_philo *philo)
// {
//     printf("%i id philo\n",philo->id);
//     printf("time_eat %i \n", (int)philo->time_eat);
//     printf("time_dead %i \n", (int)philo->time_dead);
//     printf("time_sleep %i \n", (int)philo->time_sleep);
//     printf("r_fork %i \n",philo->r_fork);
//     // printf("l_fork %i \n",philo->l_fork);
//     printf("x time %i \n",philo->xtime);
// }