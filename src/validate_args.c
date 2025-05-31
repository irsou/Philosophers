/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:09:07 by isousa-s          #+#    #+#             */
/*   Updated: 2025/05/26 19:09:07 by isousa-s         ###   ########.fr       */
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
		philos[i].last_meal = 0;
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
	data->dead = 0;
	if (argc == 6)
		data->eat_num = ft_atoi(argv[5]);
	else
		data->eat_num = -1;
	if (data->philo_num <= 0 || data->die_time <= 0
		|| data->eat_time <= 0 || data->sleep_time <= 0)
	{
		write(2, "Error: All values must be positive\n", 35);
		return (0);
	}
	if (argc == 6 && data->eat_num <= 0)
	{
		write(2, "Error: Number of meals must be positive\n", 40);
		return (0);
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				write(2, "Error: Arguments must be positive numbers\n", 42);
				return (0);
			}
			j++;
		}
		if (j == 0)
		{
			write(2, "Error: Empty argument\n", 22);
			return (0);
		}
		i++;
	}
	return (1);
}
