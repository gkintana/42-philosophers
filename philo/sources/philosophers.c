/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/24 09:07:23 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int argc, char **argv)
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (check_args(argc, argv) == FAILURE)
		return (FAILURE);
	if (args_to_struct(&info, argc, argv) == FAILURE)
		return (FAILURE);
	if (init_mutex(&info) == FAILURE)
		return (FAILURE);
	if (init_philos(&info) == FAILURE)
		return (FAILURE);
	if (simulation(&info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
