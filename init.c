/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:24:53 by pfalli            #+#    #+#             */
/*   Updated: 2024/06/13 12:24:53 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.c"

int init_philo(t_data *data)
{
    int i = 0;

    while (i < data->philo_num)
    {
        data->philos[i].count_meals = 0; 
        pthread_mutex_init(&data->philos[i].fork);
        data->philos[i].id = i;
        if (data->philo_num == 1)
            data->philos[i].id.next = 0;
        else
            data->philos[i].id_next = i = 1;
        // last_meal
        data->philos[i].data = data;
        i++;
    }
}

int check_arguments(t_data *data, int ac);
{
    if (ft_strlen(av[1]) == 0 || ft_strlen(av[2]) == 0 || ft_strlen(av[3]) == 0 || ft_strlen(av[4] == 0))
        return(error("Invalid Arguments"));
    if (data->philo_num < 1 || (ac == 6 && data->meals_num < 1))
        return(error("Invalid Arguments"));
    //  to prevent scenarios where the duration is too short, which could lead to unexpected behavior or performance issues
    if (data->time_die < 60 || data->time_eat < 60 || data->time_sleep < 60)
		return (error("Invalid arguments"));
}

int init_data(t_data *data, char **av, int ac)
{
    data->philo_num = ft_atoi(av[1]); // forks_num = philo_num
    data->time_die = ft_atoi(av[2]);
    data->time_eat = ft_atoi(av[3]);
    data->time_sleep = ft_atoi(av[4]);
    if (ac == 6)
        data->meals_num = ft_atoi(av[5]);
    data->dead = 0;
    check_arguments(&data, ac);

    // mutex init
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->eat_mutex, NULL);
    gettimeofday(&data->start_time, NULL);

    // malloc t_philo struct for the number of philos
    data->philos = malloc((t_philo *) data->phlio_num);
    init_philo(&data);
    return(0);
}
