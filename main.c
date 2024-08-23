/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:58:04 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/09 14:58:04 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_av(int ac, char **av)
{
    int i = 1;

    if (ac < 5 || ac > 6)
        return(one_and_print("only 4 o 5 arguments\n"));
    while (i < ac)
    {
        if (av[i][0] == '-')
            return(one_and_print("only positive number\n"));
        if (!ft_isnum(av[i]))
            return(one_and_print("only numbers no letters\n"));
        if (ft_strlen(av[1]) == 0 || ft_atoi(av[i]) == 0)
            return(one_and_print("args empty\n"));
        if ( i == 1 && atoi(av[1]) == 0)
            return(one_and_print("at least 1 philo\n"));
        if (atoi(av[1]) > 9999)
            return(one_and_print("too many philo\n"));
        i++; 
    }
    return(0);
}

// Main function

int	main(int ac, char **av)
{
    t_info		info;
    t_philo		philo[PHILO_MAX];

    check_av(ac, av);
    init_info(&info, philo, av);
    init_philo(philo, &info, av);
    thread_create(&info);
    destory_all(NULL, &info);
    return (0);
}