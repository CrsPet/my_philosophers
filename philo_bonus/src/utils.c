/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchopped <jchopped@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:45:42 by jchopped          #+#    #+#             */
/*   Updated: 2022/03/13 18:17:19 by jchopped         ###   ########.fr       */
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

void	clear_philo(t_philo *philo)
{
	int	i;

	i = 0;
	sem_close(philo->time);
	sem_close(philo->count);
	sem_close(philo->sem);
	sem_close(philo->all);
	sem_close(philo->print);
	free(philo->philos);
	while (i < philo->nmb)
		kill(philo->philos[i++], SIGKILL);
}

void	print_info(t_philo *philo, char *out)
{
	sem_wait(philo->print);
	printf(out, get_time(philo->start_time), philo->index + 1);
	sem_post(philo->print);
}

void	ft_sleep(t_philo *philo, long limit)
{
	long	this_start;

	this_start = get_time(philo->start_time);
	while (get_time (philo->start_time) - this_start < limit)
		usleep(3 * limit);
}
