/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:36:29 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/23 10:36:29 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

// Print message funtion

void	print_message(char *str, t_philo *philo, int id)
{
	unsigned long	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time_in_ms() - philo->start_time;
	if (!dead_loop(philo))
		printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}


int	philoopher_dead(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time_in_ms() - philo->last_meal >= (unsigned long)time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

// Check if any philo died

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philo)
	{
		if (philoopher_dead(&philo[i], philo[i].time_to_die))
		{
			print_message("died", &philo[i], philo[i].id);
			pthread_mutex_lock(philo[0].dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if all the philo ate the num_of_meals

int	check_if_all_ate(t_philo *philo)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (philo[0].num_times_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philo)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (finished_eating == philo[0].num_of_philo)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

// Monitor thread routine

void	*monitor(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philo) == 1 || check_if_all_ate(philo) == 1)
			break ;
	return (pointer);
}