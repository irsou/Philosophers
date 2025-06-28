/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:08:41 by isousa-s          #+#    #+#             */
/*   Updated: 2025/05/26 19:08:41 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_mutexes(t_data *data)
{
	int		i;

	if (data->forks)
	{
		i = 0;
		while (i < data->philo_num)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
}

void	cleanup_philosophers(t_philo *philos, int philo_num)
{
	int		i;

	if (philos)
	{
		i = 0;
		while (i < philo_num)
		{
			pthread_mutex_destroy(&philos[i].mealtime_mutex);
			i++;
		}
		free(philos);
	}
}

void	cleanup_all(t_philo *philos, t_data *data)
{
	cleanup_mutexes(data);
	cleanup_philosophers(philos, data->philo_num);
}

void	end_simulation(t_philo *philos)
{
	pthread_mutex_lock(&philos[0].data->dead_mutex);
	philos[0].data->dead = 1;
	pthread_mutex_unlock(&philos[0].data->dead_mutex);
}
