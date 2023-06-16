/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:06:12 by lpicciri          #+#    #+#             */
/*   Updated: 2023/06/16 19:48:00 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	take_drop(t_philo *philo, int i)
{
	if(i == 0)
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
	}
	if(i == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		philo->eating = 0;
		pthread_mutex_unlock(&philo->lock);
		messages("is sleeping", philo);
	}
}
void	eat(t_philo *philo)
{
	take_drop(philo,0);
	ft_usleep(philo->data->t_eat);
	take_drop(philo,1);
	ft_usleep(philo->data->t_sleep);
	messages("is thinking", philo);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	philo = (t_philo *) arg;
	while (philo->data->dead == 0)
	{
		if (philo->eating == 0 && (get_time() - philo->last_eat) > philo->data->t_die)
		{
			philo->data->dead = 1;
			messages("is died",philo);
			break;
		}
		if(philo->eaten == philo->data->n_eat)
		{
			philo->data->finished = 1;
			break;
		}
	}
	return(NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if(pthread_create(&philo->monitor_id, NULL, &monitor, philo))
	{
		printf("ERROR THREAD");
		return(NULL);
	}
	philo->eaten = 0;
	while(philo->data->dead == 0 && philo->data->finished == 0)
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
