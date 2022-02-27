/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/24 09:49:15 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	print_event(t_info *info, int who, int event)
{
	char	str[142];
	char	*str_time;
	size_t	len;
	size_t	time;

	memset(str, 0, 142);
	ft_memcpy(str, DEF CLOCK, ft_strlen(DEF CLOCK));
	len = ft_strlen(DEF CLOCK);
	time = current_time() - info->time_start;
	str_time = ft_itoa(time);
	ft_memcpy(&str[len], str_time, ft_strlen(str_time));
	len += ft_strlen(str_time);
	free(str_time);
	ft_memcpy(&str[len], MS, ft_strlen(MS));
	len += ft_strlen(MS);
	if (event == 1)
		print_hold_forks(str, who + 1, len, time);
	if (event == 2)
		print_eat(str, who + 1, len, time);
	other_events(event, str, who, len);
	write(1, str, ft_strlen(str));
}

void	print_hold_forks(char *str, int who, size_t len, size_t time)
{
	char	*str_id;

	if (time < 10)
	{
		ft_memcpy(&str[len], YELLOW FORK_1, ft_strlen(YELLOW FORK_1));
		len += ft_strlen(YELLOW FORK_1);
	}
	else
	{
		ft_memcpy(&str[len], YELLOW FORK_2, ft_strlen(YELLOW FORK_2));
		len += ft_strlen(YELLOW FORK_2);
	}
	str_id = ft_itoa(who);
	ft_memcpy(&str[len], str_id, ft_strlen(str_id));
	len += ft_strlen(str_id);
	free(str_id);
	ft_memcpy(&str[len], FORK_3 DEF, ft_strlen(FORK_3 DEF));
}

void	print_eat(char *str, int who, size_t len, size_t time)
{
	char	*str_id;

	if (time < 10)
	{
		ft_memcpy(&str[len], GREEN EAT_1, ft_strlen(GREEN EAT_1));
		len += ft_strlen(GREEN EAT_1);
	}
	else
	{
		ft_memcpy(&str[len], GREEN EAT_2, ft_strlen(GREEN EAT_2));
		len += ft_strlen(GREEN EAT_2);
	}
	str_id = ft_itoa(who);
	ft_memcpy(&str[len], str_id, ft_strlen(str_id));
	len += ft_strlen(str_id);
	free(str_id);
	ft_memcpy(&str[len], EAT_3 DEF, ft_strlen(EAT_3 DEF));
}

void	print_sleep(char *str, int who, size_t len)
{
	char	*str_id;

	ft_memcpy(&str[len], PURPLE SLEEP_1, ft_strlen(PURPLE SLEEP_1));
	len += ft_strlen(PURPLE SLEEP_1);
	str_id = ft_itoa(who);
	ft_memcpy(&str[len], str_id, ft_strlen(str_id));
	len += ft_strlen(str_id);
	free(str_id);
	ft_memcpy(&str[len], SLEEP_2 DEF, ft_strlen(SLEEP_2 DEF));
}

void	print_think(char *str, int who, size_t len)
{
	char	*str_id;

	ft_memcpy(&str[len], CYAN THINK_1, ft_strlen(CYAN THINK_1));
	len += ft_strlen(CYAN THINK_1);
	str_id = ft_itoa(who);
	ft_memcpy(&str[len], str_id, ft_strlen(str_id));
	len += ft_strlen(str_id);
	free(str_id);
	ft_memcpy(&str[len], THINK_2 DEF, ft_strlen(THINK_2 DEF));
}
