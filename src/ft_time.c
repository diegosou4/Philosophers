

#include "../includes/philo.h"


int ft_usleep(size_t milliseconds)
{
    size_t start;

    start = get_curr_time();

    while((get_curr_time() - start) < milliseconds)
        usleep(500);
    return(0);
}


size_t get_curr_time(void)
{
    struct timeval time;
    
    if(gettimeofday(&time,NULL) == -1)
    {
        write(2, "Error in get_curr_time\n",24);
    }
    return(time.tv_sec * 1000 + time.tv_usec / 1000);
}