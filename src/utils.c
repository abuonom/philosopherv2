/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:09:18 by abuonomo          #+#    #+#             */
/*   Updated: 2023/06/14 15:48:30 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

unsigned long long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"));
	return ((tv.tv_sec * (unsigned long long int)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	unsigned long long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	one_philo(t_data *data)
{
	data->start_time = get_time();
	pthread_create(&data->philo[0].tn, NULL, &routine, &data->philo[0]);
	pthread_detach(data->philo[0].tn);
	while (data->philo[0].status == DEAD)
		ft_usleep(0);
	return (0);
}
