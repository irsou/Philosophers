/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:34:35 by isousa-s          #+#    #+#             */
/*   Updated: 2025/05/31 11:52:01 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fail_mutex_init(t_data *data)
{
	cleanup_mutexes(data);
	return (0);
}

int	init_mutexes(t_data *data)
{
	static int	i = 0;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (0);
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (fail_mutex_init(data));
	if (pthread_mutex_init(&data->dead_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (fail_mutex_init(data));
	}
	return (1);
}
