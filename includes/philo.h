/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:22:51 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/23 14:55:06 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


typedef struct s_philo
{
    char **cpyenv;
    int philo;
    int eat;
    int dead;
    int stop;
    int sleep;
    int xtime;
}       t_philo;

int	ft_isdigit(char *str);
int parse_philo(int ac,char **av,char **env);
int	ft_atoi(const char *str);


#endif