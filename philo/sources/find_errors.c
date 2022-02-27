/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkintana <gkintana@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:52:04 by gkintana          #+#    #+#             */
/*   Updated: 2022/02/22 14:43:09 by gkintana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	error(int error_code)
{
	printf(RED_B ERROR);
	if (error_code == 1)
	{
		printf(RED EXPECTED YELLOW EX_01 EX_02 EX_03 EX_04 EX_05 EX_06);
		printf(CYAN NOTE_01 NOTE_02 DEF);
	}
	else if (error_code == 2)
		printf(RED INVALID DEF);
	return (FAILURE);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (error(1));
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!argv[i][j])
				return (error(1));
			else if (!ft_isdigit(argv[i][j]))
				return (error(2));
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
