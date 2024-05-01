/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:22:51 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/01 10:54:02 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct g_mutex
{
    pthread_mutex_t mutex;
}   t_mutex;

typedef struct s_philo
{
    pthread_t thread;
    int id;
    size_t time_eat;
    size_t time_dead;
    size_t time_sleep;
    int r_fork;
    int l_fork;
    int xtime;
}       t_philo;

typedef struct s_table
{
    int				dead_flag;
    pthread_mutex_t dead_lock;
    pthread_mutex_t dead_eat;
    pthread_mutex_t dead_sleep;
    t_philo *philo;
} t_table;



int	ft_isdigit(char *str);
int parse_philo(int ac,char **av);
int	ft_atoi(const char *str);
void give_philo(int ac,char **av,t_philo *philo);
void philo_init(int ac,char **av);
void print_struct(t_philo *philo);


// Time

size_t get_curr_time(void);

#endif