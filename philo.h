/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:10:12 by pfalli            #+#    #+#             */
/*   Updated: 2024/06/11 16:02:08 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
 #define PHILO_H

#include <unistd.h>
#include <sys/time.h> // gettimeofday
#include <stdlib.h> // malloc and others
#include <stdio.h> // printf
#include <stdint.h> // u_int64
#include <pthread.h> // ****it works on WSL***

//	philo_msg
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

// struct of each philo. save info regarding each philo. the info will be adjust everytime by the thread data->philos[i].""
typedef struct s_philo
{
	struct s_data	*data;
	pthread_t       thread;

	int             count_meals;
	int				last_meal; // time

	int             id;
	int             id_next;

	pthread_mutex_t	*fork;

} t_philo;

typedef struct s_data
{
	t_philo         *philos;

	int             philo_num;
	int             meals_num;
	u_int64_t       time_die;
	u_int64_t       time_eat;
	u_int64_t       time_sleep;
	
	pthread_mutex_t *forks_mutex;
	pthread_mutex_t eat_mutex;
	pthread_mutex_t print_mutex;

	int             dead;
	int             finished;
	pthread_t       *tid;
	u_int64_t       start_time;
} t_data;



#endif