/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:24:48 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/24 13:30:17 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long long	time_snap(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	printing(t_philo *philo, char *str)
{
	sem_wait(philo->data->print);
	if (!(philo->data->dead))
	{
		printf("%lld ", time_snap() - philo->data->time_start);
		printf("%d ", philo->id);
		printf("%s\n", str);
	}
	sem_post(philo->data->print);
}
