/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:14:17 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/08 20:13:46 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	init_philos(t_data *data)
{
	int	i;

	data->time_start = time_snap();
	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].id = i;
		data->philo[i].data = data;
		data->philo[i].last_meal = 0;
		pthread_create(&data->philo[i].thread, NULL,
			&philo_loop, &(data->philo[i]));
		i++;
		usleep(10);
	}
	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
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
	data->stop = 0;
	if (argv[5])
		data->num_eat = ft_atoi(argv[5]);
	if (argv[5] && data->num_eat == 0)
	{
		printf("Philosophers need to eat at least once!\n");
		return (0);
	}
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (data->philo == NULL)
		return (0);
	return (1);
}

int	init(t_data *data, char **argv)
{
	if (init_vars(data, argv) == 0)
		return (0);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->check, NULL);
	if (init_philos(data) == 0)
		return (0);
	return (1);
}
