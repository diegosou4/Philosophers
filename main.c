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

pthread_mutex_t mutex;

void *ft_try(void *nada)
{
	pthread_mutex_lock(&mutex);
	printf("comer\n");
	sleep(1);
	printf("pensar\n");
	sleep(1);
	printf("mimir\n");
	sleep(1);
	pthread_mutex_unlock(&mutex);
	return(NULL);

}

// int main(int ac,char **av, char **env)
// {
// 	pthread_t *thread;
// 	int pid;
	

// 	if(pthread_mutex_init(&mutex,NULL) != 0)
// 	{
// 		printf("pega o guanaraba e vem\n");
// 		return(0);
// 	}
// 	thread = malloc(sizeof(pthread_t) * 3);

//  	pthread_create(&(thread[0]), NULL,ft_try,NULL);
//  	pthread_create(&(thread[1]), NULL,ft_try,NULL);
//  	pthread_create(&(thread[2]), NULL,ft_try,NULL);


//  	pthread_join(thread[0], NULL);
//  	pthread_join(thread[1], NULL);
//  	pthread_join(thread[2], NULL);
// 	pthread_mutex_destroy(&mutex);

// 	return(0);
// }


int main(int ac,char **av)
{
	if(ac == 5 || ac == 6)
	{
		if(parse_philo(ac,av) == 1)
		{
			philo_init(ac,av);
		}
	}
	else{
		printf("Number Arguments Incorret!!\n");
	}
	return(0);
}
