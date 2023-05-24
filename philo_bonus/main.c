/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:07:40 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/24 15:20:29 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	clean_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		kill(data->pid[i], SIGKILL);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->meal);
	sem_close(data->print);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == 0)
		return (0);
	if (init(&data, argv) == 0)
		return (0);
	sem_post(data.check);
	return (0);
}
