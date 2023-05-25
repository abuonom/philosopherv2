/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:09:18 by abuonomo          #+#    #+#             */
/*   Updated: 2023/05/25 16:50:41 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

unsigned long long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday() FAILURE\n", NULL));
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
	pthread_create(&data->philo[0]->tn, NULL, &routine, &data->philos[0]);
	pthread_detach(data->philo[0]->tn);
	while (data->dead == 0)
		ft_usleep(0);
	return (0);
}
