/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:31:58 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/22 13:31:59 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



void monitor(t_table *table) {
    t_philo *ptr;
    while (1) {
        mutex_operation(&table->dead_lock, LOCK);
        if (table->is_dead) {
            ptr = &table->philo[table->id_dead];
            // ft_usleep(ptr->time_dead);
            print_status(ptr, DEAD);
            mutex_operation(&table->dead_lock, UNLOCK);
            exit(0);
        }
        mutex_operation(&table->dead_lock, UNLOCK);
    }
}

void start_monitor(t_table *table, int flag) {
    if (flag == START) {
        pthread_create(&table->monitor, NULL, (void *(*)(void *))monitor, (void *)table);
    } else if (flag == WAIT) {
        pthread_join(table->monitor, NULL);
    }
}