/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:42:19 by isousa-s          #+#    #+#             */
/*   Updated: 2025/06/28 10:15:00 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	track(t_philo *philos)
{
	int			i;
	static long	start_time = 0;

	if (start_time == 0)
		start_time = get_time();
	while (1)
	{
		i = 0;
		while (i < philos[0].data->philo_num)
		{
			if (check_philo_death(&philos[i], start_time))
				return ;
			i++;
		}
		if (check_all_fed(philos))
		{
			end_simulation(philos);
			return ;
		}
		usleep(1000);
	}
}
