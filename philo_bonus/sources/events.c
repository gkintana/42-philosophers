/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/27 11:21:28 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	event_single_philo(t_info *info, t_philo *philo)
{
	print_event(info, philo->id, 1);
	mod_usleep(info, info->time_to_die);
	sem_wait(info->event);
	print_event(info, philo->id, 5);
	sem_post(info->event);
	release_and_exit(info, SUCCESS);
}

void	event_hold_forks(t_info *info, t_philo *philo)
{
	sem_wait(info->fork);
	sem_wait(info->fork);
	sem_wait(info->event);
	if (!info->terminate)
	{
		print_event(info, philo->id, 1);
		print_event(info, philo->id, 1);
	}
	sem_post(info->event);
}

void	event_eat(t_info *info, t_philo *philo)
{
	sem_wait(info->event);
	if (!info->terminate)
		print_event(info, philo->id, 2);
	philo->last_meal = compute_time();
	sem_post(info->event);
	// death_monitor(info, philo);
	mod_usleep(info, info->time_to_eat);
	sem_wait(info->event);
	philo->meal_count++;
	sem_post(info->event);
}

void	event_sleep(t_info *info, t_philo *philo)
{
	sem_wait(info->event);
	if (!info->terminate)
		print_event(info, philo->id, 3);
	sem_post(info->event);
	sem_post(info->fork);
	sem_post(info->fork);
	mod_usleep(info, info->time_to_sleep);
}

void	event_think(t_info *info, t_philo *philo)
{
	sem_wait(info->event);
	if (!info->terminate)
		print_event(info, philo->id, 4);
	sem_post(info->event);
}
