

#include "../includes/philo.h"


int    ft_usleep(size_t milliseconds, t_table *table)
{
    size_t start;

    start = get_current_time();

    while((get_current_time() - start) < milliseconds)
    {
        if(end_simulation(table) == true)
            break;
        usleep(500);
    }
        
    return(0);
}


size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t time_diff(size_t time)
{
    return(get_current_time() - time);

}