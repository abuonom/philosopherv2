/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:05:30 by abuonomo          #+#    #+#             */
/*   Updated: 2023/05/23 21:26:37 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/philo.h"
#include <pthread.h>

void *routine()
{
	printf("Thread creato");
	return ((void*)0);
}

int main(int argc, char **argv)
{
	t_data data;

	if(check_input(argc,argv))
		return (printf("Errore negli input"),1);
	if(init(&data,argc,argv))
		return (printf("Errore in init"),1);
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

