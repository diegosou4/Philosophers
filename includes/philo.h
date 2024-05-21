/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:22:51 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/01 14:55:46 by diemorei         ###   ########.fr       */
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
#include <unistd.h>

typedef struct s_philo
{
    int id;
    int status;
    pthread_t thread;
    pthread_mutex_t my_mutex;
    int xtime;
    size_t time_eat;
    size_t time_dead;
    size_t time_sleep;
    size_t last_eat;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
  
}       t_philo;

typedef struct s_table
{
    int				dead_flag;
    int         qtphilo;
    int num;
    size_t start_time;
    pthread_mutex_t dead_lock;
    pthread_mutex_t dead_eat;
    pthread_mutex_t dead_sleep;
    pthread_mutex_t num_lock;
    pthread_mutex_t thinking;
    t_philo *philo;
} t_table;

enum mutexflags{
    INIT,
    DESTROY,
    LOCK,
    UNLOCK,
};

enum philoflags{
    START,
    WAIT,
    LIVE,
    DEAD
};

int	ft_isdigit(char *str);
int parse_philo(int ac,char **av);
size_t	ft_atoi(const char *str);
void give_philo(int ac,char **av,t_philo *philo);
void del_mutex_philo(t_philo *philo, int qtphilo);
void mutex_table_operation(t_table *table,int flag);
void mutex_operation(pthread_mutex_t *mutex, int flag);
void philo_init(int ac,char **av);
void print_struct(t_philo *philo);
int ft_usleep(size_t milliseconds);

// Time


size_t	get_current_time(void);
size_t time_diff(size_t time);

// Rotine 
void start_philo(t_table *table, int ac, char **av);
void philo_operation(t_table *table, int flag);
void rotine(t_table *table);
#endif