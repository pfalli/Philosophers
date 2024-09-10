/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:30:10 by pfalli            #+#    #+#             */
/*   Updated: 2024/09/10 12:30:10 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// getting input from prompt
void	init_av(t_philo *philo, char **av)
{
	philo->num_of_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->num_times_to_eat = ft_atoi(av[5]);
	else
		philo->num_times_to_eat = -1;
}

// init philos structure
void	init_philo(t_philo *philo, t_info *info, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		init_av(&philo[i], av);
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].start_time = get_current_time();
		philo[i].last_meal = get_current_time();
		philo[i].print_lock = &info->print_lock;
		philo[i].dead_lock = &info->dead_lock;
		philo[i].meal_lock = &info->meal_lock;
		philo[i].dead = &info->dead_flag;
		philo[i].l_fork = &info->forks_lock[i];
		if (i == 0)
			philo[i].r_fork = &info->forks_lock[philo[i].num_of_philo - 1];
		else
			philo[i].r_fork = &info->forks_lock[i - 1];
		i++;
	}
}

// init mutexes
void	init_info(t_info *info, t_philo *philo, char **av)
{
	int	i;

	i = 0;
	info->dead_flag = 0;
	info->philo = philo;
	pthread_mutex_init(&info->print_lock, NULL);
	pthread_mutex_init(&info->dead_lock, NULL);
	pthread_mutex_init(&info->meal_lock, NULL);
	info->philo_num = ft_atoi(av[1]);
	while (i < info->philo_num)
	{
		pthread_mutex_init(&info->forks_lock[i], NULL);
		i++;
	}
}
