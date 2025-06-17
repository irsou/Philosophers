/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isousa-s <isousa-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:09:29 by isousa-s          #+#    #+#             */
/*   Updated: 2025/05/24 10:09:29 by isousa-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>  //gettimeofday

typedef struct s_data
{
	int				philo_num;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_num;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;	
}	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;	
	pthread_mutex_t	mealtime_mutex;
}	t_philo;

//FUNCTIONS
size_t	ft_strlen(const char *str);
int		print_error(const char *msg);
int		validate_args(int argc, char **argv);
int		init_data(t_data *data, char **argv, int argc);
int		ft_atoi(const char *str);
void	cleanup_all(t_philo *philos, t_data *data);
void	*ft_memset(void *ptr, int value, size_t length);
int		init_mutexes(t_data *data);
void	*philosopher_routine(void *arg);
int		start_threads(t_philo *philos);
long	get_time(void);
int		check_death(t_philo *philo);
void	print_status(t_philo *philo, char *status);
void	cleanup_mutexes(t_data *data);
t_philo	*init_philos(t_data *data);
void	track(t_philo *philos);

#endif