/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:48:48 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/08 20:17:44 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (1);
}

void	*check_status(void *temp)
{
	t_philo		*philo;
	long int	diff;

	philo = (t_philo *)temp;
	pthread_mutex_lock(&philo->data->check);
	diff = time_snap() - philo->last_meal;
	if (is_alive(philo) && (diff) >= ((long)(philo->data->time_die)))
	{
		printf("Philosopher %d has died!\n", philo->id);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->check);
	}
	pthread_mutex_unlock(&philo->data->check);
	return (NULL);
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eating);
	usleep(philo->data->time_sleep * 1000);
	printf("Philosopher %d is thinking!\n", philo->id);
	pthread_mutex_unlock(&philo->data->eating);
}

void	*philo_loop(void *temp)
{
	t_philo		*philo;
	pthread_t	check;

	philo = (t_philo *)temp;
	while (is_alive(philo))
	{
		philo_eating(philo);
		pthread_create(&check, NULL, &check_status, philo);
	}
	return (NULL);
}
