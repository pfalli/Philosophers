/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 10:37:18 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/23 10:37:18 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	print_message(THINK, philo, philo->id);
}

void	dream(t_philo *philo)
{
	print_message(SLEEP, philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}
// lock_forks(philo, &first_fork, &second_fork);
// if (philo->num_of_philo == 1) return;
void	eat(t_philo *philo)
{
	//	pthread_mutex_t *first_fork;
    //	pthread_mutex_t *second_fork;
//	
    //	if (philo->id % 2 == 0)
    //	{
    //	    first_fork = philo->r_fork;
    //	    second_fork = philo->l_fork;
    //	}
    //	else
    //	{
    //	    first_fork = philo->l_fork;
    //	    second_fork = philo->r_fork;
    //	}
	pthread_mutex_lock(philo->r_fork);
	print_message(TAKE_FORK, philo, philo->id);
	if (philo->num_of_philo == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_message(TAKE_FORK, philo, philo->id);
	philo->eating = 1;
	print_message(EAT, philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void lock_forks(t_philo *philo, pthread_mutex_t **first_fork, pthread_mutex_t **second_fork)
{
    if (philo->id % 2 == 0)
    {
        *first_fork = philo->r_fork;
        *second_fork = philo->l_fork;
    }
    else
    {
        *first_fork = philo->l_fork;
        *second_fork = philo->r_fork;
    }
    pthread_mutex_lock(*first_fork);
    print_message(TAKE_FORK, philo, philo->id);
    if (philo->num_of_philo == 1)
    {
        ft_usleep(philo->time_to_die);
        pthread_mutex_unlock(*first_fork);
        return;
    }
    pthread_mutex_lock(*second_fork);
    print_message(TAKE_FORK, philo, philo->id);
}
