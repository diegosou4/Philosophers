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

pthread_mutex_t *mutexes;

pthread_mutex_t *my_mutex(void)
{
    static pthread_mutex_t mutex;
    return(&mutex);
}

void rotine(t_table *table) {
    int qtphilo = table->qtphilo;
    while (1 && table->philo[table->num].xtime > 0) {
        pthread_mutex_lock(&table->sal);
        printf("%zu has taken a fork %i\n",get_curr_time(), table->philo[table->num].id);
        table->philo[table->num].l_fork = &table->philo[table->num].my_mutex;
        table->philo[table->num].r_fork = &table->philo[(table->num + 1) % qtphilo].my_mutex; // Evita acesso fora do limite
        pthread_mutex_lock(table->philo[table->num].l_fork);
        pthread_mutex_lock(table->philo[table->num].r_fork);
        printf("%zu is eating %i\n",get_curr_time(),table->philo[table->num].id);
        ft_usleep(table->philo[table->num].time_eat);
        table->philo[table->num].xtime--;
        pthread_mutex_unlock(table->philo[table->num].l_fork);
        pthread_mutex_unlock(table->philo[table->num].r_fork);
        printf("%zu is sleeping %i\n",get_curr_time(),table->philo[table->num].id);
        ft_usleep(table->philo[table->num].time_sleep);
        printf("%zu is thinking %i\n",get_curr_time(),table->philo[table->num].id);
        printf("\n");
        // printf("%i xtime\n", table->philo[table->num].xtime);
        // printf("%i table num\n", table->num);
        pthread_mutex_unlock(&table->sal);
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

    pthread_mutex_init(&table->sal, NULL);

    ptr = table->philo;
    for(i = 0; i < qtphilo; i++)
    {
        printf("philo id aqui %i\n", ptr[i].id);
    }
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

    pthread_mutex_destroy(&table->sal);

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