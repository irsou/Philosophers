/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:34:35 by isousa-s          #+#    #+#             */
/*   Updated: 2025/06/28 12:04:14 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->philo_num)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_meal = data->start_time;
		philos[i].data = data;
		philos[i].left_fork = &data->forks[i];
		philos[i].right_fork = &data->forks[(i + 1) % data->philo_num];
		pthread_mutex_init(&philos[i].mealtime_mutex, NULL);
		i++;
	}
	return (philos);
}

int	init_data(t_data *data, char **argv, int argc)
{
	data->philo_num = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->start_time = get_time();
	data->dead = 0;
	if (argc == 6)
		data->eat_num = ft_atoi(argv[5]);
	else
		data->eat_num = -1;
	if (data->philo_num <= 0 || data->die_time <= 0
		|| data->eat_time <= 0 || data->sleep_time <= 0)
		return (print_error("Error: All values must be positive\n"));
	if (argc == 6 && data->eat_num <= 0)
		return (print_error("Error: Number of meals must be positive\n"));
	return (1);
}

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
