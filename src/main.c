/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:05:14 by isousa-s          #+#    #+#             */
/*   Updated: 2025/05/31 11:56:15 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	static int		exit_code = 0;
	int				i;

	ft_memset(&data, 0, sizeof(t_data));
	philos = NULL;
	if (argc == 5 || argc == 6)
	{
		if (!validate_args(argc, argv) || !init_data(&data, argv, argc))
			exit_code = 1;
		else if (!init_mutexes(&data))
		{
			write(2, "Error: Failed to initialize mutexes\n", 37);
			exit_code = 1;
		}
		else
		{
			philos = init_philos(&data);
			if (!philos)
			{
				write(2, "Error: Failed to initialize philosophers\n", 41);
				exit_code = 1;
			}
			else if (!start_threads(philos))
			{
				write(2, "Error: Failed to start threads\n", 31);
				exit_code = 1;
			}
			else
			{
				track(philos);
				i = 0;
				while (i < data.philo_num)
				{
					pthread_join(philos[i].thread, NULL);
					i++;
				}
			}
		}
	}
	else
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		exit_code = 1;
	}
	cleanup_all(philos, &data);
	return (exit_code);
}
