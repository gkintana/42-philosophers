/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/27 11:39:39 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	*death_monitor(void *ptr)
{
	t_info	*info;
	t_philo	*philo;

	philo = (struct s_philo *)ptr;
	info = philo->info;
	while (!info->terminate)
	{
		check_time_of_last_meal(info, philo);
		usleep(500);
		sem_wait(info->event);
		if (info->terminate || philo->meal_count == info->meal_limit)
		{
			sem_post(info->event);
			break ;
		}
		sem_post(info->event);
	}
	return (NULL);
}

void	check_time_of_last_meal(t_info *info, t_philo *philo)
{
	sem_wait(info->event);
	if (compute_time() - philo->last_meal >= (size_t)info->time_to_die + 5)
	{
		if (!info->terminate)
		{
			print_event(info, philo->id, 5);
			info->terminate = 1;
		}
		release_and_exit(info, FAILURE);
	}
	sem_post(info->event);
}

void	print_death(char *str, int who, size_t len)
{
	char	*str_id;

	ft_memcpy(&str[len], RED DEATH_1, ft_strlen(RED DEATH_1));
	len += ft_strlen(RED DEATH_1);
	str_id = ft_itoa(who);
	ft_memcpy(&str[len], str_id, ft_strlen(str_id));
	len += ft_strlen(str_id);
	free(str_id);
	ft_memcpy(&str[len], DEATH_2 DEF, ft_strlen(DEATH_2 DEF));
}
