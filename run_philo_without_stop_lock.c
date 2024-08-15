/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:19:32 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/12 12:19:32 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor(void *pointer)
{
    t_info *info = (t_info *)pointer;
    int  i = 0;

    while (1)
    {
        while (i < info->num_philo)
        {
            if (philo_alive(&info->philo_array[i]) == 0)
                return (NULL);
            usleep(100); // to reduce CPU usage in the monitor loop
        }
    }
    return NULL;
}

// checking death_flag inside each philo_array[i] info
int philo_alive(t_philo *philo)
{
    unsigned long current_time;

    pthread_mutex_lock(&philo->info->dead_lock);
    current_time = get_time_in_ms();
    if ((current_time - philo->last_meal_time) >= (unsigned long)philo->info->time_die)
    {
        if(philo->info->death == 0)
        {
            ft_print_action(philo, DIED);
            philo->info->death = 1;
        }
        pthread_mutex_unlock(&philo->info->dead_lock);
        return (0);
    }
    if (philo->info->death == 1)
    {
        pthread_mutex_unlock(&philo->info->dead_lock);
        return (0);
    }
    pthread_mutex_unlock(&philo->info->dead_lock);
    return (1);
}


void *routine (void *argument)
{
    t_philo *philo;

    philo = (t_philo *)argument;
    if (philo->info->num_philo == 1)
	{
		ft_print_action(philo, TAKE_FORK);
		ft_usleep(philo->info->time_die);
		ft_print_action(philo, DIED);
		philo->info->death = 1;
		return (NULL);
	}
    while (philo_alive(philo))
    {
        // Take forks
        lock_forks(philo);

        // Eat
        pthread_mutex_lock(&philo->info->meal_lock);
        philo->last_meal_time = get_time_in_ms();
        ft_print_action(philo, EATING);
        ft_usleep(philo->info->time_eat);
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->info->meal_lock);

        // Release forks
        pthread_mutex_unlock(&philo->info->forks_lock[philo->id]);
        pthread_mutex_unlock(&philo->info->forks_lock[(philo->id + 1) % philo->info->num_philo]);

        // Sleep
        ft_print_action(philo, SLEEPING);
        ft_usleep(philo->info->time_sleep);

        // Think
        ft_print_action(philo, THINKING);
    }
    return (NULL);
}

int run_philo(t_info *info)
{
    int i = 0;

    info->philo_array = calloc(info->num_philo, sizeof(t_philo));
    if (info->philo_array == NULL)
        return(one_and_print("error allocation run_philo\n"));
        //***monitor ***/
    if (pthread_create(&info->death_thread, NULL, monitor, info) != 0)
            return (one_and_print("error threads: run_philo\n"));

    while (i <= info->num_philo)
    {
        info->philo_array[i].id = i;
        info->philo_array[i].last_meal_time = info->start_time;
        info->philo_array[i].meals_eaten = 0;
        info->philo_array[i].info = info;
        if (pthread_create(&info->philo_array[i].philo_thread, NULL, routine, &info->philo_array[i]) != 0)
            return (one_and_print("error threads: run_philo\n"));
        i++;
    }
    i = 0;
    if (pthread_join(info->death_thread, NULL) != 0)
            return (one_and_print("error joining: run_philo\n"));
    while (i <= info->num_philo)
    {
        if (pthread_join(info->philo_array[i].philo_thread, NULL) != 0)
            return (one_and_print("error joining: run_philo\n"));
        i++;
    }
    return 0;
}