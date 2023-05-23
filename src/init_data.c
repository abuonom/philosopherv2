/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:56:52 by abuonomo          #+#    #+#             */
/*   Updated: 2023/05/23 23:36:53 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep
//[number_of_times_each_philosopher_must_eat]

int init(t_data *data,int argc,char **argv)
{
	if(init_tdata(data,argc,argv))
		return (1);
	if(alloc_tdata(data))
		return (1);
	if(init_thread(data))
		return (1);
	return (0);
}

int	init_tdata(t_data *data,int argc,char **argv)
{
	if(argc == 6)
		data->nr_eat = (int)ft_atoi(argv[5]);
	data->nr_philo = (int)ft_atoi(argv[1]);
	data->die_time = (unsigned long long)ft_atoi(argv[2]);
	data->eat_time = (unsigned long long)ft_atoi(argv[3]);
	data->sleep_time = (unsigned long long)ft_atoi(argv[4]);
	if(data->nr_philo <= 0 || data->nr_philo > 200 || data->die_time <= 0
		|| data->eat_time <= 0 || data->sleep_time <= 0)
		return (1);
	return (0);
}

int alloc_tdata(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->nr_philo);
	if(!data->philo)
		return (1);
	return (0);
}

int init_thread(t_data *data)
{
	int i = -1;
	while(++i < data->nr_philo)
	{
		data->philo->p_id = i;
		pthread_create(&data->philo[i].pn, NULL, &routine, NULL);
	}
	i = -1;
	while(++i < data->nr_philo)
		pthread_join(data->philo[i].pn, NULL);
	return (0);
}
