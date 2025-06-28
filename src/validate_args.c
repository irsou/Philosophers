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

int	is_valid_number_string(const char *str)
{
	int	j;

	if (!str)
		return (0);
	j = 0;
	while (str[j])
	{
		if (str[j] < '0' || str[j] > '9')
			return (0);
		j++;
	}
	return (j > 0);
}

int	is_valid_range(const char *str)
{
	long	value;

	value = atol(str);
	return (value > 0 && value <= 2147483647);
}

int	validate_single_arg(const char *arg)
{
	if (!is_valid_number_string(arg))
	{
		if (arg && arg[0] == '\0')
			return (print_error("Error: Empty argument\n"));
		else
			return (print_error("Error: Arguments must be positive numbers\n"));
	}
	if (!is_valid_range(arg))
		return (print_error("Error: Argument out of valid integer range\n"));
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!validate_single_arg(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
