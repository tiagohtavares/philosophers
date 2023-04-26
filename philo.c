/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:07:40 by ttavares          #+#    #+#             */
/*   Updated: 2023/04/26 15:27:07 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	count = 0;
pthread_mutex_t	lock;

void	*counter()
{
	int	i;

	i = 0;
	pthread_mutex_lock(&lock);
	while (i < 1000000)
	{
		i++;
		count++;
	}
	pthread_mutex_unlock(&lock);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	test1;
	pthread_t	test2;

	(void)argc;
	(void)argv;
	pthread_mutex_init(&lock, NULL);
	pthread_create(&test1, NULL, &counter, NULL);
	pthread_create(&test2, NULL, &counter, NULL);

	pthread_join(test1, NULL);
	pthread_join(test2, NULL);
	pthread_mutex_destroy(&lock);
	printf("Counter: %d \n", count);
	return (0);
}
