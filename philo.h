/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:59:46 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/09 14:59:46 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft_full/inc/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

//	philo_msg
# define TAKE_FORK "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"
# define LEAVE_FORKS "has put down forks"


typedef struct s_info
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				got_food;
	int				death;
	unsigned long	start_time;

	int stop;
    pthread_t check_death;
	pthread_mutex_t stop_lock;

	pthread_mutex_t sleep_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks_lock; // same number of philos
	struct s_philo	*philo_array;

}										t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		philo_thread;
	unsigned long	last_meal_time;
	int				meals_eaten;
	t_info			*info;

}										t_philo;


int				get_info(int ac, char **av, t_info **info);
int				init_mutex(t_info *info);
int				run_philo(t_info *info);
void			ft_print_action(t_philo *philo, char *action);
void 			*routine (void *argument);
void			free_info(t_info *info);
int 			philo_alive(t_philo *philo);
void 			lock_forks(t_philo *philo);
void			*monitor(void *pointer);
void stop_philosophers(t_info *info, t_philo *philo_array, int num_philo);

int             one_and_print(char *message);
unsigned long	get_time_in_ms(void);
int				ft_isnum(char *str);
int				ft_usleep(useconds_t time);

#endif