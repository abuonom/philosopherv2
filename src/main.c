/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:05:30 by abuonomo          #+#    #+#             */
/*   Updated: 2023/05/24 18:04:18 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <pthread.h>

/*
◦ number_of_philosophers: The number of philosophers and also the number
of forks.
◦ time_to_die (in milliseconds):Se un filosofo non entra nello stato EAT entro time_to_die, dal suo
	ultimo pranzo o dall'inizio della simulazione muore.
◦ time_to_eat (in milliseconds): Il tempo che un filosofo rimane nello stato EAT,
	per entrarci deve possedere 2 forks
◦ time_to_sleep (in milliseconds): Tempo per il quale dorme
◦ number_of_times_each_philosopher_must_eat (optional argument): Le volte che un filosofo deve mangiare
							per far si che la simulazione termina.
							Naturalmente, se un filosofo muore essa termina comunque.
*/



//credo che la routine vada implementata come segue:
//Il filosofo, prova a prendere le due forchette
//di conseguenza mangia per il tempo previsto STATUS 1
//poi pensa per il tempo previsto STATUS 2
//poi dorme per il tempo previsto STATUS 3

void eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	philo->status = EAT;
	printf("%llu ms %d is eating",get_time(),philo->p_id);
	ft_usleep(philo->data->eat_time);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->status = SLEEP;
	ft_usleep(philo->data->sleep_time);
}

void *routine(t_philo *philo)
{
	while(philo->status != DEAD)
	{
	eat(philo);
	printf("%llu ms %d is thinking",get_time(),philo->p_id);
	ft_usleep(philo->data->think_time);
	}
}

int main(int argc, char **argv)
{
	t_data data;

	if(check_input(argc,argv))
		return (printf("Errore negli input"),1);
	if(init(&data,argc,argv))
		return (printf("Errore in init"),1);
	if(data.nr_philo == 1) //necessariamente solo un filosofo dovrà morire
							//dopo aver atteso il suo tempo di morte.
		one_philo();
}
	//CODEVAULT SPIEGAZIONE THREAD E MUTEX
/*	void* routine()
{
	for(int i = 0; i < 10000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}
	pthread_t t1, t2, t3, t4;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_create(&t3, NULL, &routine, NULL);
	pthread_create(&t4, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n",mails);
	return (0);
}
*/

