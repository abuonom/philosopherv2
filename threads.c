/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:06:12 by lpicciri          #+#    #+#             */
/*   Updated: 2023/06/15 18:43:48 by abuonomo         ###   ########.fr       */
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
	philo->eating = 1;
	philo->last_eat = get_time();
	messages("is eating", philo);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	messages("is sleeping", philo);
	ft_usleep(philo->data->t_sleep);
	messages("is thinking", philo);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *) arg;
	while (1)
	{
		if (philo->eating == 0 && (get_time() - philo->last_eat) > philo->data->t_die)
		{
			philo->data->dead = true;
			messages("is died",philo);
			ft_usleep(10000);
			return(NULL);
		}
	}
	return(NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_create(&philo->monitor_id, NULL, &monitor, philo);
	philo->eaten = 0;
	while(philo->data->dead == false && philo->eaten != philo->data->n_eat)
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
		pthread_create(&data->thread_id[i], NULL, &routine, &data->philo[i]);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->thread_id[i], NULL);
	return (0);
}
