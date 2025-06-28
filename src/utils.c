/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 11:44:47 by isousa-s          #+#    #+#             */
/*   Updated: 2025/06/28 12:43:19 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->mealtime_mutex);
	philo->last_meal = get_time();
	printf("Tiempo actual: %ld\n", get_time() - philo->data->start_time);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mealtime_mutex);
	usleep(philo->data->eat_time * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}


int	handle_single_philo(t_philo *philo)
{
	if (philo->data->philo_num == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		usleep(philo->data->die_time * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	should_exit(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	if (philo->data->eat_num != -1 && philo->eat_count >= philo->data->eat_num)
		return (1);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->eat_time * 500);
	while (!check_death(philo))
	{
		if (philo->data->eat_num != -1
			&&philo->eat_count >= philo->data->eat_num)
			break ;
		philo_eat(philo);
		if (check_death(philo))
			break ;
		print_status(philo, "is sleeping");
		usleep(philo->data->sleep_time * 1000);
		if (check_death(philo))
			break ;
		print_status(philo, "is thinking");
	}
	return (NULL);
}
