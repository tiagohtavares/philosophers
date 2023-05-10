/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:08:33 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/08 20:17:21 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	long int			last_meal;
	pthread_t			thread;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				num_eat;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				stop;
	long int		time_start;
	t_philo			*philo;
	pthread_mutex_t	eating;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	check;
}	t_data;



int			check_args(int argc, char **argv);
int			init(t_data *data, char **argv);
int			ft_atoi(const char *str);
long long	time_snap(void);
void		*philo_loop(void *temp);

#endif
