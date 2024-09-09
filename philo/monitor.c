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

void	print_message(char *str, t_philo *philo, int id)
{
	unsigned long	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%ld %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->print_lock);
}


int	philosopher_dead(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= (unsigned long)time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philo)
	{
		if (philosopher_dead(&philo[i], philo[i].time_to_die))
		{
			print_message(DIE, &philo[i], philo[i].id);
			pthread_mutex_lock(philo[0].dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_got_food(t_philo *philo)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	if (philo[0].num_times_to_eat == -1)
		return (0);
	while (i < philo[0].num_of_philo)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_times_to_eat)
			ate++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (ate == philo[0].num_of_philo)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

// Monitor thread
void	*monitor(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philo) == 1 || all_got_food(philo) == 1)
			break ;
	return (pointer);
}