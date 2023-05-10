/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:07:40 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/10 12:06:45 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	clean_exit(t_data *data)
{
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->check);
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
