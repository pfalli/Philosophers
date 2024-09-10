/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:28:26 by pfalli            #+#    #+#             */
/*   Updated: 2024/09/10 12:28:26 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(char *str, t_info *info)
{
	int	i;

	i = 0;
	if (str)
		ft_printf("%s\n", str);
	pthread_mutex_destroy(&info->print_lock);
	pthread_mutex_destroy(&info->meal_lock);
	pthread_mutex_destroy(&info->dead_lock);
	while (i < info->philo_num)
	{
		pthread_mutex_destroy(&info->forks_lock[i]);
		i++;
	}
}

int	check_av(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (one_and_print("❌ only 4 o 5 arguments\n"));
	while (i < ac)
	{
		if (av[i][0] == '-')
			return (one_and_print("❌ only positive numbers\n"));
		if (!ft_isnum(av[i]))
			return (one_and_print("❌ only numbers no letters\n"));
		if (ft_strlen(av[1]) == 0 || ft_atoi(av[i]) == 0)
			return (one_and_print("❌ args empty\n"));
		if (i == 1 && atoi(av[1]) == 0)
			return (one_and_print("❌ at least 1 philo\n"));
		if (atoi(av[1]) > 9999)
			return (one_and_print("❌ too many philo\n"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_philo		philo[PHILO_MAX];

	if (check_av(ac, av) == 1)
		return (1);
	init_info(&info, philo, av);
	init_philo(philo, &info, av);
	run_threads(&info);
	free_mutex(NULL, &info);
	return (0);
}
