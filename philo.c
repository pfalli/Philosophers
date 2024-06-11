/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:10:16 by pfalli            #+#    #+#             */
/*   Updated: 2024/06/11 16:05:24 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if digits and bigger than 0 
int check_arguments(char *av)
{
    int i = 0;

    while (av[i])
    {
        if (!is_digit(av[i]))
            return(0);
        i++;
    }
    return(1);
}

void init(t_philo philo)
{
    philo->
    philo->
    philo->
}

int main (int ac, char **av)
{
    if (ac == 5)
    {
        
    }
    else
        printf("Error: only 5 parameters allowed\n")
}