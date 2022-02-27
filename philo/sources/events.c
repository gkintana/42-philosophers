/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/24 12:23:26 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*event_single_philo(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->fork[philo->fork_current]);
	print_event(info, philo->id, 1);
	mod_usleep(info, info->time_to_die);
	pthread_mutex_unlock(&info->fork[philo->fork_current]);
	pthread_mutex_lock(&info->event);
	print_event(info, philo->id, 5);
	pthread_mutex_unlock(&info->event);
	return (NULL);
}

void	event_hold_forks(t_info *info, t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&info->fork[philo->fork_current]);
		pthread_mutex_lock(&info->fork[philo->fork_next]);
	}
	else
	{
		pthread_mutex_lock(&info->fork[philo->fork_next]);
		pthread_mutex_lock(&info->fork[philo->fork_current]);
	}
	pthread_mutex_lock(&info->event);
	if (!info->terminate)
	{
		print_event(info, philo->id, 1);
		print_event(info, philo->id, 1);
	}
	pthread_mutex_unlock(&info->event);
}

void	event_eat(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->event);
	if (!info->terminate)
		print_event(info, philo->id, 2);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&info->event);
	mod_usleep(info, info->time_to_eat);
	pthread_mutex_lock(&info->event);
	philo->meal_count++;
	pthread_mutex_unlock(&info->event);
}

void	event_sleep(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->event);
	if (!info->terminate)
		print_event(info, philo->id, 3);
	pthread_mutex_unlock(&info->event);
	pthread_mutex_unlock(&info->fork[philo->fork_current]);
	pthread_mutex_unlock(&info->fork[philo->fork_next]);
	mod_usleep(info, info->time_to_sleep);
}

void	event_think(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->event);
	if (!info->terminate)
		print_event(info, philo->id, 4);
	pthread_mutex_unlock(&info->event);
}
