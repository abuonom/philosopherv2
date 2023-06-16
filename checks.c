/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:47:32 by lpicciri          #+#    #+#             */
/*   Updated: 2023/06/16 18:42:17 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	only_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((argv[i][j] < 48 || argv[i][j] > 57))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (-1);
	if (only_digits(argv) == -1)
		return (-1);
	return (0);
}

void free_all(t_data *data)
{
	if (data->thread_id)
		free(data->thread_id);
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}
