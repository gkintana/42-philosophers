/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/25 12:40:30 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	death_monitor(t_info *info, t_philo *philo)
{
	int	i;

	while (info->count > 1 && !info->end_simulation)
	{
		i = -1;
		while (++i < info->count && !info->terminate)
			check_time_of_last_meal(info, philo, i);
		pthread_mutex_lock(&info->event);
		if (info->terminate)
		{
			pthread_mutex_unlock(&info->event);
			break ;
		}
		i = 0;
		while ((info->meal_limit != -1) && (i < info->count)
			&& (philo[i].meal_count >= info->meal_limit))
			i++;
		if (i == info->count)
			info->end_simulation = 1;
		pthread_mutex_unlock(&info->event);
	}
}

void	check_time_of_last_meal(t_info *info, t_philo *philo, int i)
{
	pthread_mutex_lock(&info->event);
	if (current_time() - philo[i].last_meal > (size_t)info->time_to_die + 5)
	{
		print_event(info, i, 5);
		info->terminate = 1;
	}
	pthread_mutex_unlock(&info->event);
	usleep(1000);
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
