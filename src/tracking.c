/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:42:19 by isousa-s          #+#    #+#             */
/*   Updated: 2025/05/31 11:56:15 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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

void	print_status(t_philo *philo, char *status)
{
	long		timestamp;
	static long	start_time = 0;

	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (start_time == 0)
		start_time = get_time();
	timestamp = get_time() - start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	track(t_philo *philos)
{
	int			i;
	int			all_fed;
	long		current_time;
	long		time_since_meal;
	static long	start_time = 0;

	if (start_time == 0)
		start_time = get_time();
	while (1)
	{
		i = 0;
		all_fed = 1;
		while (i < philos[0].data->philo_num)
		{
			pthread_mutex_lock(&philos[i].mealtime_mutex);
			current_time = get_time();
			time_since_meal = current_time - philos[i].last_meal;
			pthread_mutex_unlock(&philos[i].mealtime_mutex);
			if (time_since_meal > philos[i].data->die_time)
			{
				pthread_mutex_lock(&philos[i].data->dead_mutex);
				philos[i].data->dead = 1;
				pthread_mutex_unlock(&philos[i].data->dead_mutex);
				pthread_mutex_lock(&philos[i].data->print_mutex);
				printf("%ld %d died\n", current_time - start_time,
					philos[i].id);
				pthread_mutex_unlock(&philos[i].data->print_mutex);
				return ;
			}
			if (philos[i].data->eat_num != -1
				&& philos[i].eat_count < philos[i].data->eat_num)
				all_fed = 0;
			i++;
		}
		if (philos[0].data->eat_num != -1 && all_fed)
		{
			pthread_mutex_lock(&philos[0].data->dead_mutex);
			philos[0].data->dead = 1;
			pthread_mutex_unlock(&philos[0].data->dead_mutex);
			return ;
		}
		usleep(1000);
	}
}
