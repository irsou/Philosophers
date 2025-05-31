/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:05:14 by isousa-s          #+#    #+#             */
/*   Updated: 2025/05/27 20:40:44 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philos;
	static int		exit_code = 0;

	ft_memset(&data, 0, sizeof(t_data));
	philos = NULL;
	if (argc == 5 || argc == 6)
	{
		if (!validate_args(argc, argv) || !init_data(&data, argv, argc))
			exit_code = 1;
		/*philos = init_philosophers(&data);
		if (!philos)
			exit_code = 1;
		start_threads(philos);
		monitor(philos);*/
	}
	else
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		exit_code = 1;
	}
	cleanup_all(philos, &data);
	return (exit_code);
}
