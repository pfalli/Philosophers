/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:58:04 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/09 14:58:04 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_info(t_info *info)
{
	int	index;

	index = 0;
	if (info)
	{
		if (info->forks_lock)
		{
			while (index < info->num_philo)
			{
				pthread_mutex_destroy(&(info->forks_lock[index]));
                pthread_mutex_destroy(&info->print_lock);
	            pthread_mutex_destroy(&info->meal_lock);
	            pthread_mutex_destroy(&info->dead_lock);
                pthread_mutex_destroy(&info->sleep_lock);
				index++;
			}
			free(info->forks_lock);
		}
		if (info->philo_array)
			free(info->philo_array);
		free(info);
	}
}


void print_av(t_info *info)
{
    printf("num_philo: %d\n", info->num_philo);
    printf("time_die: %d\n", info->time_die);
    printf("time_eat: %d\n", info->time_eat);
    printf("time_sleep: %d\n", info->time_sleep);
    printf("must_eat: %d\n", info->must_eat);
    printf("start_time: %ld\n", info->start_time);
}

int main(int ac, char **av)
{
    t_info *info;
    int result = 0;

    result = get_info(ac, av, &info);
    if (result != 0)
    {
        free_info(info);
        return(one_and_print("get_info issue\n"));
    }
    print_av(info);
    printf("\n*** running info***\n");

    result = init_mutex(info);
    if (result != 0)
    {
        free_info(info);
        return(one_and_print("init_mutex issue\n"));
    }

    result = run_philo(info);
    free_info(info);
    return(result);
}
