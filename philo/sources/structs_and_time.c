/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_and_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/24 23:06:46 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	args_to_struct(t_info *info, int argc, char **argv)
{
	info->count = philosopher_atoi(argv[1]);
	if (info->count < 1)
		return (error(2));
	info->time_to_die = philosopher_atoi(argv[2]);
	if (info->time_to_die <= 0 || info->time_to_die > INT_MAX)
		return (error(2));
	info->time_to_eat = philosopher_atoi(argv[3]);
	if (info->time_to_eat <= 0 || info->time_to_eat > INT_MAX)
		return (error(2));
	info->time_to_sleep = philosopher_atoi(argv[4]);
	if (info->time_to_sleep <= 0 || info->time_to_sleep > INT_MAX)
		return (error(2));
	if (argc == 6)
	{
		info->meal_limit = philosopher_atoi(argv[5]);
		if (info->meal_limit < 1)
			return (error(2));
	}
	else
		info->meal_limit = -1;
	info->terminate = 0;
	info->end_simulation = 0;
	return (SUCCESS);
}

int	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->count)
	{
		info->philo[i].info = info;
		info->philo[i].id = i;
		info->philo[i].meal_count = 0;
		info->philo[i].last_meal = 0;
		info->philo[i].fork_current = i;
		info->philo[i].fork_next = (i + 1) % info->count;
	}
	return (SUCCESS);
}

size_t	current_time(void)
{
	struct timeval	current;
	size_t			time;

	gettimeofday(&current, NULL);
	time = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (time);
}

void	mod_usleep(t_info *info, size_t event_time)
{
	size_t	start_of_sleep;

	start_of_sleep = current_time();
	while (1)
	{
		pthread_mutex_lock(&info->event);
		if (info->terminate || current_time() - start_of_sleep >= event_time)
		{
			pthread_mutex_unlock(&info->event);
			break ;
		}
		pthread_mutex_unlock(&info->event);
		usleep(100);
	}
}
