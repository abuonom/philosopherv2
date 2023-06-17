/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 20:06:55 by abuonomo          #+#    #+#             */
/*   Updated: 2023/06/17 20:07:01 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	case_one(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->thread_id[0], NULL, &routine, &data->philo[0]))
		return (-1);
	pthread_detach(data->thread_id[0]);
	while (data->finished == 0)
		ft_usleep(0);
	free_all(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == -1)
		return (printf("Error: wrong arguments\n"));
	if (init(&data, argv) == -1)
		return (printf("Error: init_data\n"));
	return (0);
}
