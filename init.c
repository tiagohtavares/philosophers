/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:14:17 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/26 13:38:32 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	start_philos(t_data *data)
{
	int	i;

	i = 0;
	data->time_start = time_snap();
	while (i < data->num_philo)
	{
		data->philo[i].last_meal = time_snap();
		pthread_create(&(data->philo[i].thread), NULL, loop, &(data->philo[i]));
		i++;
		usleep(1000);
	}
	philo_manager(data);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

int	init_philos_extra(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].id = i;
		data->philo[i].meal_count = 0;
		data->philo[i].left_fork_id = i;
		data->philo[i].right_fork_id = (i + 1) % data->num_philo;
		data->philo[i].data = data;
		i++;
	}
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_philo % 2 != 0)
	{
		while (i < data->num_philo)
		{
			data->philo[i].id = i;
			data->philo[i].meal_count = 0;
			data->philo[i].right_fork_id = i;
			data->philo[i].left_fork_id = (i + 1) % data->num_philo;
			data->philo[i].data = data;
			i++;
		}
	}
	else if (data->num_philo % 2 == 0)
	{
		init_philos_extra(data);
	}
	return (1);
}

int	init_vars(t_data *data, char **argv)
{
	if (ft_atoi(argv[1]) == 0)
	{
		printf("No philosophers, need at least one!\n");
		return (0);
	}
	data->num_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->all_finished_eat = 0;
	data->dead = 0;
	if (argv[5])
	{
		data->num_eat = ft_atoi(argv[5]);
		if (data->num_eat == 0)
		{
			printf("Philosophers need to eat at least once!\n");
			return (0);
		}
	}
	else
		data->num_eat = -1;
	return (1);
}

int	init(t_data *data, char **argv)
{
	int	i;

	i = 0;
	if (init_vars(data, argv) == 0)
		return (0);
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (data->philo == NULL)
		return (0);
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->print, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (data->forks == NULL)
		return (0);
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	if (init_philos(data) == 0)
		return (0);
	start_philos(data);
	return (1);
}
