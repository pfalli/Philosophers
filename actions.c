/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:24:06 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/15 08:24:06 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void ft_print_action(t_philo *philo, char *action)
{
    unsigned long current_time = get_time_in_ms() - philo->info->start_time;

    pthread_mutex_lock(&philo->info->print_lock);
    printf("time: %ld philo[%d] %s\n", current_time, philo->id, action);
    pthread_mutex_unlock(&philo->info->print_lock);
}

void lock_forks(t_philo *philo)
{
    if (philo->id < (philo->id + 1) % philo->info->num_philo)
    {
        pthread_mutex_lock(&philo->info->forks_lock[philo->id]);
        ft_print_action(philo, TAKE_FORK);
        pthread_mutex_lock(&philo->info->forks_lock[(philo->id + 1) % philo->info->num_philo]);
        ft_print_action(philo, TAKE_FORK);
    }
    else
    {
        pthread_mutex_lock(&philo->info->forks_lock[(philo->id + 1) % philo->info->num_philo]);
        ft_print_action(philo, TAKE_FORK);
        pthread_mutex_lock(&philo->info->forks_lock[philo->id]);
        ft_print_action(philo, TAKE_FORK);
    }
}