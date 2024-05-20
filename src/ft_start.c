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
    printf("%zu %d is thinking\n",time_diff(table->start_time),table->philo[id].id);
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

    while (1 && table->philo[id].xtime  > 0 || table->philo[id].xtime == -1) 
    {
        table->start_time = get_current_time();
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
    table->philo = malloc(sizeof(t_philo) * qtphilo);
    table->qtphilo = qtphilo; // Adicione esta linha para armazenar o número total de filósofos
    // Inicialização dos filósofos
    for (i = 0; i < qtphilo; i++)
    {
        give_philo(ac, av, &table->philo[i]);
        table->philo[i].qtphilo = qtphilo;
    }

    pthread_mutex_init(&table->dead_lock, NULL);
    pthread_mutex_init(&table->dead_eat, NULL);
    pthread_mutex_init(&table->dead_sleep, NULL);
    pthread_mutex_init(&table->num_lock, NULL);

    ptr = table->philo;
    // for(i = 0; i < qtphilo; i++)
    // {
    //     printf("philo id aqui %i\n", ptr[i].id);
    // }
    table->num = 0;
    // Criação das threads
    for (i = 0; i < qtphilo; i++)
    {
        pthread_create(&ptr[i].thread, NULL, (void *(*)(void *))rotine, (void *)table);
        
    }

    // Espera pelas threads
    for (i = 0; i < qtphilo; i++)
    {
        pthread_join(ptr[i].thread, NULL);
        table->num++;
    }
    for(i = 0; i < qtphilo; i++)
    {
         pthread_mutex_destroy(&ptr[i].my_mutex);
    }

    pthread_mutex_destroy(&table->num_lock);
    pthread_mutex_destroy(&table->dead_lock);
    pthread_mutex_destroy(&table->dead_eat);
    pthread_mutex_destroy(&table->dead_sleep);

    // Liberação de memória
    free(mutexes);
    free(table->philo);
    free(table);
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