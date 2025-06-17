/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:08:56 by isousa-s          #+#    #+#             */
/*   Updated: 2025/05/26 19:08:56 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t		position;

	position = 0;
	while (str[position] != '\0')
		position ++;
	return (position);
}

int	print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

int	ft_atoi(const char *str)
{
	int		result;
	int		i;

	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

void	*ft_memset(void *ptr, int value, size_t length)
{
	size_t			pos;
	unsigned char	*dir;

	pos = 0;
	dir = ptr;
	while (pos < length)
	{
		dir[pos] = (unsigned char)value;
		pos++;
	}
	return (dir);
}
