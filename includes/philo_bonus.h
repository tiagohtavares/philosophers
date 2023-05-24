/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttavares <ttavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:08:33 by ttavares          #+#    #+#             */
/*   Updated: 2023/05/24 15:07:59 by ttavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <signal.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_philo
{
	int					id;
	int					meal_count;
	long int			last_meal;
	pthread_t			manager;
	pthread_t			thread;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				*pid;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				dead;
	int				all_finished_eat;
	long int		time_start;

	sem_t			*forks;
	sem_t			*meal;
	sem_t			*print;
	sem_t			*check;
	t_philo			*philo;
}	t_data;

int			check_args(int argc, char **argv);
int			init(t_data *data, char **argv);
int			ft_atoi(const char *str);
long long	time_snap(void);
void		*loop(void *temp);
void		printing(t_philo *philo, char *str);
void	philo_manager(t_data *data);
void		clean_exit(t_data *data);

#endif
