/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:53:43 by abuonomo          #+#    #+#             */
/*   Updated: 2023/06/12 18:12:47 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#endif

#define EAT 1
#define SLEEP 2
#define THINK 3
#define DEAD 4
typedef struct s_philo
{
	int				p_id;
	int				status;
	struct s_data	*data;
	pthread_t		tn;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
	unsigned long long int	death_time;
}t_philo;

typedef struct s_data
{
	int						nr_philo;
	int						nr_eat;
	unsigned long long int	start_time;
	unsigned long long int	eat_time;
	unsigned long long int	think_time;
	unsigned long long int	sleep_time;
	unsigned long long int	die_time;
	pthread_mutex_t			*forks;
	int						end;
	t_philo *philo;
}t_data;



int	check_input(int argc, char **argv);
int	is_in_strings(char c, char *str);
long	ft_atoi(const char *str);
int	init_tdata(t_data *data,int argc,char **argv);
int init(t_data *data,int argc,char **argv);
int alloc_tdata(t_data *data);
void* routine();
int init_thread(t_data *data);
unsigned long long int	get_time(void);
int	ft_usleep(useconds_t time);
int	one_philo(t_data data);
void *monitor(t_data *data);
