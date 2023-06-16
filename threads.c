/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:06:12 by lpicciri          #+#    #+#             */
/*   Updated: 2023/06/16 21:47:01 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void *monitor(void *args)
{
	t_philo *philo = (t_philo *)args;
	while(philo->data->finished)
	{
		if(philo->eaten != philo->data->n_eat)
			philo->data->finished = 1;
		if(get_time() - philo->last_eat > philo->t_die && philo->eating == 0)
		{
			messages("is died",philo);
			philo->data->finished = 1;
		}
	}
	return NULL;
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	messages("take L FORK",philo);
	pthread_mutex_lock(philo->r_fork);
	messages("take R FORK",philo);
	pthread_mutex_lock(&philo->lock);
	philo->eaten++;
	philo->eating = 1;
	philo->last_eat = get_time();
	messages("is eating",philo);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->eating = 0;
	pthread_mutex_unlock(philo->lock);
	messages("is sleeping",philo);
	ft_usleep(philo->data->t_sleep);
	messages("is thinking",philo);
}

void *routine(void *args)
{
	t_philo *philo = (t_philo *)args;

	pthread_create(&philo->monitor_id,NULL, &monitor,philo);
	while(philo->data->finished == 0)
	{
		eat(philo);
	}
	return (NULL);
}

int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->n_philo)
		if(pthread_create(&data->thread_id[i], NULL, &routine, &data->philo[i]))
			return (-1);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->thread_id[i], NULL);
	free_all(data);
	return (0);
}
