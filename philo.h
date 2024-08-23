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
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>

/* errors */
# define WRONG_NUM_ARGS "❌ Error: Wrong number of arguments"
# define WRONG_ARG_TYPE "❌ Error: Numeric arguments required"
# define NUM_PHILO "❌ Error: Number of philosophers must be at least 1"
# define DIE_TIME "❌ Error: Time to die must be at least 1"
# define EAT_TIME "❌ Error: Time to eat must be at least 1"
# define SLEEP_TIME "❌ Error: Time to sleep must be at least 1"
# define NUM_EAT "❌ Error: Number of times to eat must be at least 1"
# define MALLOC_FAIL "❌ Error: Malloc failed"
# define THREAD_CREATE_FAIL "❌ Error: Thread create failed"
# define THREAD_JOIN_FAIL "❌ Error: Thread join failed"
# define MUTEX_FAIL "❌ Error: Mutex failed"
# define TIME_FAIL "❌ Error: Time failed"
# define FORK_FAIL "❌ Error: Fork failed"
# define JOIN_FAIL "❌ Error: Join failed"
# define UNLOCK_FAIL "❌ Error: Unlock failed"
# define LOCK_FAIL "❌ Error: Lock failed"
# define MALLOC_FAIL "❌ Error: Malloc failed"

# define PHILO_MAX 300


typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					eating;
	int					meals_eaten;

	unsigned long		last_meal;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	unsigned long		start_time;

	int					num_of_philo;
	int					num_times_to_eat;
	int					*dead;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
	
}					t_philo;

typedef struct s_info
{
	int				dead_flag;
	int 			philo_num;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	forks[PHILO_MAX];
	t_philo			*philo;
}					t_info;

// Main functions
int					check_av(int ac, char **av);
void				destory_all(char *str, t_info *info);

// Initialization
void	init_info(t_info *info, t_philo *philos, char **av);
void	init_forks(t_info *info, int philo_num); // Update signature
void	init_philo(t_philo *philos, t_info *info, char **av); // Update signature
void				init_input(t_philo *philo, char **av);

// Threads
int					thread_create(t_info *info);
void				*monitor(void *pointer);
void				*philo_routine(void *pointer);

// Actions
void				eat(t_philo *philo);
void				dream(t_philo *philo);
void				think(t_philo *philo);

// Monitor utils
int					dead_loop(t_philo *philo);
int					check_if_all_ate(t_philo *philos);
int					check_if_dead(t_philo *philos);
int					philoopher_dead(t_philo *philo, int time_to_die);

// Utils
int	ft_usleep(useconds_t time);
void				print_message(char *str, t_philo *philo, int id);
unsigned long			get_time_in_ms(void);
int one_and_print(char *message);
int	ft_isnum(char *str);

// put in fd
int					has_only_digits(char *s);
void				ft_putendl_fd(char *s, int fd);

#endif