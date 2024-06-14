/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:29:11 by pfalli            #+#    #+#             */
/*   Updated: 2024/06/12 10:29:11 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// first create the threads in LOOP

// after pthread_join them

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int i = 0;

    // take forks + mutex fork

    // eat

    //leave forks + unlock fork

    // sleep

    // thinking
}

