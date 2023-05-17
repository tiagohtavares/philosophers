/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:48:48 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/17 01:33:16 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	philo_manager(t_data *data)
{
	int	i;

	while (!(data->all_finished_eat))
	{
		i = 0;
		while (i < data->num_philo && !(data->dead))
		{
			pthread_mutex_lock(&data->meal);
			if ((time_snap() - data->philo[i].last_meal) > data->time_die)
			{
				printing(&data->philo[i], "died");
				data->dead = 1;
			}
			pthread_mutex_unlock(&data->meal);
			i++;
		}
		if (data->dead)
			break ;
		i = 0;
		while (data->num_eat != -1 && i < data->num_philo
			&& data->philo[i].meal_count >= data->num_eat)
			i++;
		if (i == data->num_philo)
			data->all_finished_eat = 1;
	}
}

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork_id]);
	printing(philo, "has taken a fork");
	if (philo->data->num_philo == 1)
	{
		usleep(philo->data->time_die * 1100);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id]);
			return ;
		}
	}
	pthread_mutex_lock(&philo->data->forks[philo->right_fork_id]);
	printing(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->meal);
	printing(philo, "is eating");
	philo->last_meal = time_snap();
	pthread_mutex_unlock(&philo->data->meal);
	usleep(philo->data->time_eat * 1000);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork_id]);
}

void	*loop(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	if (philo->id % 2)
		usleep(15000);
	while (!(philo->data->dead))
	{
		philo_eating(philo);
		if (philo->data->all_finished_eat)
			break ;
		if (philo->data->dead)
			break ;
		printing(philo, "is sleeping");
		usleep(philo->data->time_sleep * 1000);
		printing(philo, "is thinking");
	}
	return (NULL);
}
