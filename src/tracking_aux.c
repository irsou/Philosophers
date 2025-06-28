/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:42:19 by isousa-s          #+#    #+#             */
/*   Updated: 2025/06/28 12:44:18 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	long	current_time;
	long	time_since_meal;

	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	pthread_mutex_lock(&philo->mealtime_mutex);
	current_time = get_time();
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->mealtime_mutex);
	if (time_since_meal > philo->data->die_time)
		return (1);
	return (0);
}

int	check_philo_death(t_philo *philo)
{
	long	current_time;
	long	time_since_meal;

	pthread_mutex_lock(&philo->mealtime_mutex);
	current_time = get_time();
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->mealtime_mutex);
	if (time_since_meal > philo->data->die_time)
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d died\n", current_time - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		printf("check_death_is_1\n");
		return (1);
	}
	return (0);
}

int	check_all_fed(t_philo *philos)
{
	int	i;

	if (philos[0].data->eat_num == -1)
		return (0);
	i = 0;
	while (i < philos[0].data->philo_num)
	{
		pthread_mutex_lock(&philos[i].mealtime_mutex);
		if (philos[i].eat_count < philos[i].data->eat_num)
		{
			pthread_mutex_unlock(&philos[i].mealtime_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].mealtime_mutex);
		i++;
	}
	return (1);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = get_time() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

