/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_and_time.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/24 23:06:18 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

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
	}
	return (SUCCESS);
}

size_t	compute_time(void)
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

	start_of_sleep = compute_time();
	while (1)
	{
		sem_wait(info->event);
		if (info->terminate || compute_time() - start_of_sleep >= event_time)
		{
			sem_post(info->event);
			break ;
		}
		sem_post(info->event);
		usleep(100);
	}
}
