/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:05:14 by isousa-s          #+#    #+#             */
/*   Updated: 2025/06/05 12:36:20 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	execute_philosophers(t_data *data, t_philo **philos, int argc, char **argv)
{
	int	i;

	if (!validate_args(argc, argv) || !init_data(data, argv, argc))
		return (1);
	if (!init_mutexes(data))
		return (print_error("Error: Failed to initialize mutexes\n"));
	*philos = init_philos(data);
	if (!*philos)
		return (print_error("Error: Failed to initialize philosophers\n"));
	if (!start_threads(*philos))
		return (print_error("Error: Failed to start threads\n"));
	track(*philos);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join((*philos)[i].thread, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;

	ft_memset(&data, 0, sizeof(t_data));
	philos = NULL;
	if (argc == 5 || argc == 6)
		execute_philosophers(&data, &philos, argc, argv);
	else
		return (print_error("Error: Invalid number of arguments\n"));
	cleanup_all(philos, &data);
	return (0);
}
