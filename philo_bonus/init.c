/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:14:17 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/24 15:25:05 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	start_philos(t_data *data)
{
	int	i;

	i = 0;
	data->time_start = time_snap();
	data->pid = (int *)malloc(sizeof(int) * data->num_philo);
	while (i < data->num_philo)
	{
		data->philo[i].last_meal = time_snap();
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			loop(data->philo + i);
		i++;
		usleep(1000);
	}
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philo[i].id = i;
		data->philo[i].meal_count = 0;
		data->philo[i].data = data;
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

void	init_sem(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("check");
	sem_unlink("meal");
	data->print = sem_open("print", O_CREAT, 0600, 1);
	data->meal = sem_open("meal", O_CREAT, 0600, 1);
	data->check = sem_open("check", O_CREAT, 0600, 1);
	data->forks = sem_open("forks", O_CREAT, 0600, data->num_philo);
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
	init_sem(data);
	if (init_philos(data) == 0)
		return (0);
	start_philos(data);
	return (1);
}
