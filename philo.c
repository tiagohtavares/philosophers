/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:48:48 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/10 14:15:07 by ttavares         ###   ########.fr       */
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
		printing(philo, "died");
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->check);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->check);
	return (NULL);
}

void	philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork_id]);
	printing(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork_id]);
	printing(philo, "has taken a fork");

}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eating);
	philo->last_meal = time_snap();
	printing(philo, "philo is eating");
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(&philo->data->eating);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id]);
	printing(philo, "philo is sleeping");
	usleep(philo->data->time_sleep * 1000);
	printing(philo, "is thinking");
}

void	*philo_loop(void *temp)
{
	t_philo		*philo;
	pthread_t	check;

	philo = (t_philo *)temp;
	while (is_alive(philo))
	{
		pthread_create(&check, NULL, &check_status, philo);
		philo_take_fork(philo);
		philo_eating(philo);
	}
	return (NULL);
}
