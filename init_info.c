/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:26:37 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/09 17:26:37 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_info(t_info **info)
{
    *info = malloc(sizeof(t_info));
    if (!info)
        return(1);
    (*info)->num_philo = 0;
    (*info)->time_die = 0;
    (*info)->time_eat = 0;
    (*info)->time_sleep = 0;
    (*info)->must_eat = 0;
    (*info)->got_food = 0;
    (*info)->death = 0;
    (*info)->start_time = 0;
    (*info)->forks_lock = NULL;
    return(0);
}

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
            return(one_and_print("too many philos\n"));
        i++; 
    }
    return(0);
}

void fill_info(t_info *info, char **av)
{
    info->num_philo = ft_atoi(av[1]);
    info->time_die = ft_atoi(av[2]);
    info->time_eat = ft_atoi(av[3]);
    info->time_sleep = ft_atoi(av[4]);
    if (av[5])
        info->must_eat = ft_atoi(av[5]);
    info->got_food = 0;
    info->start_time = get_time_in_ms();

}



int get_info(int ac, char **av, t_info **info)
{
    int result = 0;

    result = check_av(ac, av);
    if(result != 0)
        return(result);
    result = init_info(info);
    if(result != 0)
        return(result);
    fill_info(*info, av);
    (*info)->start_time = get_time_in_ms();
    if ((*info)->start_time == 0)
        return( one_and_print("error settin start_time: get_info\n"));
    return(result);
}