/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:53:43 by abuonomo          #+#    #+#             */
/*   Updated: 2023/05/23 20:40:37 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#endif

struct s_data
{
	int nr_philo;
	int nr_eat;
	unsigned long long int eat_time;
	unsigned long long int think_time;
	unsigned long long int sleep_time;
	unsigned long long int die_time;
	t_philo *philo;
}typedef t_data;

struct s_philo
{
	struct s_data *data;
	pthread_t pn;
}typedef t_philo;

int	check_input(int argc, char **argv);
int	is_in_strings(char c, char *str);
long	ft_atoi(const char *str);
int	init_tdata(t_data *data,int argc,char **argv);
int init(t_data *data,int argc,char **argv);
int alloc_tdata(t_data *data,int argc,char **argv);
