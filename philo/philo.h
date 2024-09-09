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
# include "libft_full/inc/ft_printf.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define TAKE_FORK "has taken a fork"
# define DIE "\033[1;91mdied\033[0;39m 💀"

//	# define EAT "\033[3;93mis eating 🍕\033[0;39m"
//	# define SLEEP "\033[4;95mis sleeping 🌙\033[0;39m"
//	# define THINK "\033[1;90mis thinking 💭\033[0;39m"
//	# define TAKE_FORK "\033[5;94mhas taken a fork 🍴\033[0;39m"
//	# define DIE "\033[41;91mdied\033[0;39m 💀"

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eating;
	int					meals_eaten;

	size_t		last_meal;
	size_t					time_to_die;
	size_t					time_to_eat;
	size_t					time_to_sleep;
	size_t		start_time;

	int					num_of_philo;
	int					num_times_to_eat;
	int					*dead;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*print_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	
}					t_philo;

typedef struct s_info
{
	int				dead_flag;
	int 			philo_num;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	forks_lock[PHILO_MAX];
	t_philo			*philo;
}					t_info;

// main.c
int					main(int ac, char **av);
int					check_av(int ac, char **av);
void				free_mutex(char *str, t_info *info);

// init.c
void				init_info(t_info *info, t_philo *philos, char **av);
void				init_philo(t_philo *philos, t_info *info, char **av);
void				init_av(t_philo *philo, char **av);

// Threads
int					run_threads(t_info *info);
int					dead_loop(t_philo *philo);
void				*routine(void *pointer);

// routine.c
void				eat(t_philo *philo);
void				dream(t_philo *philo);
void				think(t_philo *philo);

// Monitor utils
void				*monitor(void *pointer);
int					all_got_food(t_philo *philos);
int					check_if_dead(t_philo *philos);
int					philosopher_dead(t_philo *philo, int time_to_die);
void				print_message(char *str, t_philo *philo, int id);

// Utils
int					ft_usleep(size_t milliseconds);
size_t				get_current_time(void);
int					one_and_print(char *message);
int					ft_isnum(char *str);

#endif