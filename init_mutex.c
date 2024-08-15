/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:29:13 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/12 10:29:13 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_info *info)
{
	int	index;

	index = 0;
	if (pthread_mutex_init(&(info->sleep_lock), NULL) != 0)
		return (one_and_print("error mutex sleep_lock\n"));
	if (pthread_mutex_init(&(info->meal_lock), NULL) != 0)
		return (one_and_print("error mutex meal_lock\n"));
	if (pthread_mutex_init(&(info->print_lock), NULL) != 0)
		return (one_and_print("error mutex print_lock\n"));
	if (pthread_mutex_init(&(info->dead_lock), NULL) != 0)
		return (one_and_print("error mutex dead_lock\n"));
	// init forks_locks
	info->forks_lock = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	if (!info->forks_lock)
		return (one_and_print("error malloc init_mutexs\n"));
	while (index < info->num_philo)
	{
		if (pthread_mutex_init(&(info->forks_lock[index]), NULL) != 0)
			return (one_and_print("error mutex forks_lock\n"));
		index++;
	}
	return (0);
}