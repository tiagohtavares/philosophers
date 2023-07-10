/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:07:40 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/26 12:02:08 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	clean_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal);
	free(data->forks);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == 0)
		return (0);
	if (init(&data, argv) == 0)
		return (0);
	clean_exit(&data);
	return (0);
}
