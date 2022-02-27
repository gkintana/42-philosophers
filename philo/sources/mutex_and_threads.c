/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_and_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/25 13:01:43 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->count)
		if (pthread_mutex_init(&info->fork[i++], NULL) != 0)
			return (FAILURE);
	if (pthread_mutex_init(&info->event, NULL) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	simulation(t_info *info)
{
	t_philo		*philo;
	int			i;

	philo = info->philo;
	info->time_start = current_time();
	printf(EVENT_TITLE);
	i = -1;
	while (++i < info->count)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (FAILURE);
		usleep(250);
	}
	monitor_then_destroy(info, philo);
	return (SUCCESS);
}

void	*routine(void *ptr)
{
	t_philo		*philo;
	t_info		*info;

	philo = (struct s_philo *)ptr;
	info = philo->info;
	pthread_mutex_lock(&info->event);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&info->event);
	if (info->count == 1)
		return (event_single_philo(info, philo));
	while (1)
	{
		event_hold_forks(info, philo);
		event_eat(info, philo);
		event_sleep(info, philo);
		event_think(info, philo);
		pthread_mutex_lock(&info->event);
		if (info->terminate || philo->meal_count == info->meal_limit)
		{
			pthread_mutex_unlock(&info->event);
			break ;
		}
		pthread_mutex_unlock(&info->event);
	}
	return (NULL);
}

void	monitor_then_destroy(t_info *info, t_philo *philo)
{
	int	i;

	death_monitor(info, info->philo);
	i = 0;
	while (i < info->count)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	while (i < info->count)
		pthread_mutex_destroy(&info->fork[i++]);
	pthread_mutex_destroy(&info->event);
}
