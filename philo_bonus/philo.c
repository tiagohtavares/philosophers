/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:48:48 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/24 15:28:34 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"



void	philo_eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	printing(philo, "has taken a fork");
	if (philo->data->num_philo == 1)
	{
		usleep(philo->data->time_die * 1100);
		if (philo->data->dead)
		{
			sem_post(philo->data->forks);
			return ;
		}
	}
	sem_wait(philo->data->forks);
	printing(philo, "has taken a fork");
	sem_wait(philo->data->meal);
	printing(philo, "is eating");
	philo->last_meal = time_snap();
	sem_post(philo->data->meal);
	usleep(philo->data->time_eat * 1000);
	philo->meal_count++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}
void	philo_manager(t_data *data)
{
	int	i;

	while (!(data->all_finished_eat))
	{
		i = 0;
		while (i < data->num_philo && !(data->dead))
		{
			sem_wait(data->meal);

			if ((time_snap() - data->philo[i].last_meal) > data->time_die)
			{
				printing(&data->philo[i], "died");
				data->dead = 1;
			}
			sem_post(data->meal);
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
void	*check_status(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	while(philo->meal_count < num_eat)
	{
		while (!philo->data->dead)
		{
			sem-wait(philo->data->meal);
			if ((time_snap() =))
		}
	}
}

void	*loop(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	pthread_create(&manager, NULL, check_status, &philo);
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
	exit(0);
}
