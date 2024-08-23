/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:36:06 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/23 10:36:06 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Initializing the input from user

void	init_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philo = ft_atoi(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

// Initializing the philoophers

void	init_philo(t_philo *philo, t_info *info, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		init_input(&philo[i], argv);
		philo[i].start_time = get_time_in_ms();
		philo[i].last_meal = get_time_in_ms();
		philo[i].write_lock = &info->write_lock;
		philo[i].dead_lock = &info->dead_lock;
		philo[i].meal_lock = &info->meal_lock;
		philo[i].dead = &info->dead_flag;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[philo[i].num_of_philo - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}

// Initializing the forks mutexes

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

// Initializing the info structure

void	init_info(t_info *info, t_philo *philo)
{
	info->dead_flag = 0;
	info->philo = philo;
	pthread_mutex_init(&info->write_lock, NULL);
	pthread_mutex_init(&info->dead_lock, NULL);
	pthread_mutex_init(&info->meal_lock, NULL);
	
}