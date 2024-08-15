/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfalli <pfalli@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:14:53 by pfalli            #+#    #+#             */
/*   Updated: 2024/08/09 15:14:53 by pfalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int one_and_print(char *message)
{
    printf("%s\n", message);
    return(1);
}

unsigned long	get_time_in_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_isnum(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;
	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < time)
		ft_usleep(time / 10);
	return(0);
}

