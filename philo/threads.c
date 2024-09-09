/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:37:40 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/23 10:37:40 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks if the value of dead_flag changed
int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

// philos routine
void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

// Creates all the threads
int	run_threads(t_info *info)
{
    pthread_t	observer;
    int			i;

    if (pthread_create(&observer, NULL, &monitor, info->philo) != 0)
        free_mutex("error create observer thread", info);
    i = 0;
    while (i < info->philo[0].num_of_philo)
    {
        if (pthread_create(&info->philo[i].thread, NULL, &routine,
                &info->philo[i]) != 0)
            free_mutex("error create philo threads", info);
        i++;
    }
    i = 0;
    if (pthread_join(observer, NULL) != 0)
        free_mutex("error join observer", info);
    while (i < info->philo[0].num_of_philo)
    {
        if (pthread_join(info->philo[i].thread, NULL) != 0)
            free_mutex("error join philo threads", info);
        i++;
    }
    return (0);
}