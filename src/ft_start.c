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

void rotine(t_philo *philo) {
    while(philo->xtime > 0 || philo->xtime == -1)
    {
    pthread_mutex_lock(&mutexes[0]);
    printf("%i Comer \n",(int)get_curr_time());
    printf("%i Pensar \n",(int)get_curr_time());
    printf("%i Mimir \n",(int)get_curr_time());
    printf("\n");
    ft_usleep(philo->time_eat);
    
    pthread_mutex_unlock(&mutexes[0]);
    if(philo->xtime > 0)
        philo->xtime -= 1;
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
    // Inicialização dos filósofos
    for (i = 0; i < qtphilo; i++)
    {
        give_philo(ac, av, &table->philo[i]);
        table->philo[i].qtphilo = qtphilo;
    }

    mutexes = malloc(sizeof(pthread_mutex_t) * qtphilo);
    for (i = 0; i < qtphilo; i++) {
    pthread_mutex_init(&mutexes[i], NULL);
    // Bloqueie todos os mutexes exceto o primeiro
    if (i != 0) {
        pthread_mutex_lock(&mutexes[i]);
    }
}

    ptr = table->philo;

    // Criação das threads
    for (i = 0; i < qtphilo; i++)
    {
        pthread_create(&ptr[i].thread, NULL, (void *(*)(void *))rotine, &ptr[i]);
    }

    // Espera pelas threads
    for (i = 0; i < qtphilo; i++)
    {
        pthread_join(ptr[i].thread, NULL);
    }

    // Destruição do mutex

   for (i = 0; i < qtphilo; i++) {
    pthread_mutex_destroy(&mutexes[i]);
    }
    free(mutexes);
    // Liberação de memória
    free(table->philo);
    free(table);
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