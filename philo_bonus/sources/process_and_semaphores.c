/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and_semaphores.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/27 11:33:56 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	init_semaphore(t_info *info)
{
	sem_unlink("fork");
	sem_unlink("event");
	info->fork = sem_open("fork", O_CREAT | O_EXCL, S_IRWXU, info->count);
	info->event = sem_open("event", O_CREAT | O_EXCL, S_IRWXU, 1);
	return (SUCCESS);
}

int	simulation(t_info *info)
{
	t_philo		*philo;
	int			i;

	philo = info->philo;
	printf(EVENT_TITLE);
	info->time_start = compute_time();
	i = -1;
	while (++i < info->count)
	{
		philo[i].process = fork();
		if (philo[i].process == 0)
			routine(info, &philo[i]);
		usleep(100);
	}
	wait_then_release(info);
	return (SUCCESS);
}

void	routine(t_info *info, t_philo *philo)
{
	sem_wait(info->event);
	philo->last_meal = compute_time();
	sem_post(info->event);
	if (info->count == 1)
		event_single_philo(info, philo);
	pthread_create(&philo->monitor, NULL, death_monitor, philo);
	while (1)
	{
		event_hold_forks(info, philo);
		event_eat(info, philo);
		event_sleep(info, philo);
		event_think(info, philo);
		sem_wait(info->event);
		if (info->terminate || philo->meal_count == info->meal_limit)
		{
			sem_post(info->event);
			break ;
		}
		sem_post(info->event);
	}
	pthread_join(philo->monitor, NULL);
	release_and_exit(info, SUCCESS);
}

void	release_and_exit(t_info *info, int exit_type)
{
	sem_close(info->fork);
	sem_close(info->event);
	sem_unlink("fork");
	sem_unlink("event");
	if (exit_type == SUCCESS)
		exit(EXIT_SUCCESS);
	else if (exit_type == FAILURE)
		exit(EXIT_FAILURE);
	else
		return ;
}

void	wait_then_release(t_info *info)
{
	t_philo		*philo;
	int			status;
	int			i;

	status = 0;
	i = -1;
	while (++i < info->count)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
			break ;
	}
	philo = info->philo;
	i = -1;
	while (++i < info->count)
		kill (philo[i].process, SIGKILL);
	release_and_exit(info, RETURN);
}
