/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:06:12 by lpicciri          #+#    #+#             */
/*   Updated: 2023/06/15 12:54:12 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	messages("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	messages("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock);
	philo->eaten++;
	messages("is eating", philo);
	ft_usleep(philo->data->t_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	messages("is sleeping", philo);
	ft_usleep(philo->data->t_sleep);
}

void	*monitor(void *arg)
{
	t_data	*data;
	data = (t_data *) arg;
	int		i;

	i = 0;
	printf("monitor\n");
	while (data->dead == 0)
	{
		printf("I=%d, %d \n",i,data->philo[i].eaten);
		if (data->philo[i].eaten >= 1 && (get_time() - data->philo[i].last_eat) > data->t_die)
		{
			data->finished = 1;
			data->dead = i;
			return(NULL);
		}
		i++;
		if(i == data->n_philo)
			i = 0;
	}
	return(NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->eaten = 0;
	while(philo->dead == false && philo->eaten != philo->data->n_eat)
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
	pthread_create(&data->monitor_id, NULL, &monitor, data);
	while (++i < data->n_philo)
		pthread_create(&data->thread_id[i], NULL, &routine, &data->philo[i]);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->thread_id[i], NULL);
	pthread_join(data->monitor_id, NULL);
	return (0);
}
