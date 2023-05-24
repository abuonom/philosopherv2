/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:56:52 by abuonomo          #+#    #+#             */
/*   Updated: 2023/05/24 17:06:35 by abuonomo         ###   ########.fr       */
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
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_philo);
	if(!data->philo)
		return (1);
	return (0);
}

int init_thread(t_data *data)
{
	int i = -1;
	while(++i < data->nr_philo)
	{
		data->philo[i]->p_id = i;
		data->philo[i].status = THINK;
		pthread_create(&data->philo[i].tn, NULL, &routine, &data->philo[i].tn);
	}
	i = -1;
	while(++i < data->nr_philo)
		pthread_join(data->philo[i].tn, NULL);
	return (0);
}

int init_forks(t_data *data)
{
	int i = -1;

	while(++i < data->nr_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while(++i < data->nr_philo)
	{
		if(i == data->nr_philo - 1)
		{
		data->philo[i]->l_fork = data->forks[i];
		data->philo[i]->r_fork = data->forks[0];
		}else
		{
		data->philo[i]->s_fork = data->forks[i];
		data->philo[i]->r_fork = data->forks[i+1];
		}
	}
}
