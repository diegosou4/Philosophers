/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diemorei <diemorei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:22:51 by diegmore          #+#    #+#             */
/*   Updated: 2024/05/27 19:56:00 by diemorei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		my_mutex;
	bool				is_full;
	int					count_meals;
	size_t				last_eat;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	t_table				*table;

}						t_philo;

typedef struct s_table
{
	bool				is_dead;
	bool				end;
	bool				sync;
	int					max_meals;
	int					qtphilo;
	pthread_t			main;
	size_t				start_time;
	size_t				time_eat;
	size_t				time_dead;
	size_t				time_sleep;
	pthread_mutex_t		check;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		printf_lock;
	t_philo				*philo;
}						t_table;

enum					e_mutexflags
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
};

enum					e_philoflags
{
	START,
	WAIT,
	LIVE,
	DEAD,
	TAKE,
	EAT,
	SLEEP,
	THINK
};

// Parse
int						ft_isdigit(char *str);
int						ft_atoi(const char *str);
size_t					ft_atoil(const char *str);
void					give_philo(t_philo *philo, t_table *table);
int						parse_philo(int ac, char **av);
void					philo_init(int ac, char **av);
void					give_forks(t_philo *philo);
void					start_philo(t_table *table, int ac, char **av);
void					philo_operation(t_table *table);

// Rotine
void					print_status(t_philo *philo, int status);
bool					take_fork(t_philo *philo);
void					eat(t_philo *philo, t_table *table);
void					sleep_philo(t_philo *philo, t_table *table);
void					thinking(t_philo *philo);
void					rotine(t_philo *philo);

// Main Rotine
void					main_rotine(t_table *table);
bool					dead_all_philos(t_table *table);
bool					last_eat(t_philo *philo, t_table *table);

// Macros
bool					get_bool(pthread_mutex_t *mutex, bool *is_dead);
void					set_bool(pthread_mutex_t *mutex, bool *dest,
							bool value);
long					get_long(pthread_mutex_t *mutex, size_t *value);
void					set_long(pthread_mutex_t *mutex, size_t *dest,
							long value);

// Mutex
void					mutex_table_operation(t_table *table, int flag);
void					mutex_operation(pthread_mutex_t *mutex, int flag);
void					del_mutex_philo(t_table *table);

// Time and Sync
void					thread_syncrinize(t_table *table);
bool					end_simulation(t_table *table);
int						ft_usleep(size_t milliseconds, t_table *table);
size_t					get_current_time(void);
size_t					time_diff(size_t time);

//

void					free_philo(t_table *table);

#endif