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
