/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:53:10 by jchopped          #+#    #+#             */
/*   Updated: 2022/03/13 17:39:36 by jchopped         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(long align)
{
	long			ret;
	struct timeval	c_time;

	if (-1 == gettimeofday(&c_time, NULL))
		return (0);
	ret = c_time.tv_sec * 1000;
	ret += c_time.tv_usec * 0.001;
	return (ret - align);
}

void	ft_sleep(long limit)
{
	long	this_start;

	this_start = get_time(0);
	usleep (0.7 * limit);
	while (get_time (0) - this_start < limit)
		usleep(500);
}

void	print_info(t_philo *philo, char *out, int index)
{
	pthread_mutex_lock(&philo->print);
	if (!philo->stop)
		printf(out, get_time(philo->members[index].start_time), index + 1);
	pthread_mutex_unlock(&philo->print);
}

int	clear_philo(t_philo *philo)
{
	size_t	i;

	i = 0;
	if (!pthread_mutex_unlock(&philo->print))
		pthread_mutex_destroy(&philo->print);
	if (philo->locks)
	{
		while (i < philo->nmb)
		{
			pthread_mutex_destroy(&philo->locks[i]);
			pthread_mutex_unlock(&philo->members[i].time_lock);
			pthread_mutex_destroy(&philo->members[i].time_lock);
			i++;
		}
		free(philo->locks);
	}
	if (philo->members)
		free (philo->members);
	return (1);
}
