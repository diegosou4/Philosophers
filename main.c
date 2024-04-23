/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diegmore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:22:36 by diegmore          #+#    #+#             */
/*   Updated: 2024/04/23 14:56:04 by diegmore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/philo.h"

void *ft_try(void *nada)
{
	printf("comer\n");
	sleep(1);
	printf("pensar\n");
	sleep(1);
	printf("mimir\n");
	sleep(1);
	return(NULL);

}

int main(int ac,char **av, char **env)
{
	pthread_t *thread;
	int pid;

	thread = malloc(sizeof(pthread_t) * 10);

 	pthread_create(&(thread[0]), NULL,ft_try,NULL);
 	pthread_create(&(thread[1]), NULL,ft_try,NULL);
 	pthread_create(&(thread[2]), NULL,ft_try,NULL);
 	pthread_create(&(thread[3]), NULL,ft_try,NULL);
 	pthread_create(&(thread[4]), NULL,ft_try,NULL);
 	pthread_create(&(thread[5]), NULL,ft_try,NULL);
 	pthread_create(&(thread[6]), NULL,ft_try,NULL);
 	pthread_create(&(thread[7]), NULL,ft_try,NULL);
 	pthread_create(&(thread[8]), NULL,ft_try,NULL);
 	pthread_create(&(thread[9]), NULL,ft_try,NULL);
 	pthread_create(&(thread[10]), NULL,ft_try,NULL);

 	pthread_join(thread[0], NULL);
 	pthread_join(thread[1], NULL);
 	pthread_join(thread[2], NULL);
 	pthread_join(thread[3], NULL);
 	pthread_join(thread[4], NULL);
 	pthread_join(thread[5], NULL);
 	pthread_join(thread[6], NULL);
 	pthread_join(thread[7], NULL);
 	pthread_join(thread[8], NULL);
 	pthread_join(thread[9], NULL);
 	pthread_join(thread[10], NULL);

	return(0);
}
