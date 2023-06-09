/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:46:57 by lpicciri          #+#    #+#             */
/*   Updated: 2023/06/16 23:21:47 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdint.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				eaten;
	int				eating;
	u_int64_t		last_eat;
	u_int64_t		t_die;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	lock;
	pthread_t		monitor_id;
}	t_philo;

typedef struct s_data
{
	int					n_philo;
	u_int64_t			t_die;
	u_int64_t			t_eat;
	u_int64_t			t_sleep;
	u_int64_t			start_time;
	int					n_eat;
	int					finished;
	int					enough;
	pthread_t			*thread_id;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
}	t_data;

int			check_args(int argc, char **argv);
bool		is_in_strings(char c, char *str);
long		ft_atoi(const char *str);
int			init(t_data *data, char **argv);
int			init_threads(t_data *data);
int			init_data(t_data *data, char **argv);
int			alloc(t_data *data);
void		eat(t_philo *philo);
int			ft_usleep(useconds_t time);
u_int64_t	get_time(void);
void		messages(char *str, t_philo *philo);
void		free_all(t_data *data);
int			ft_strcmp(char *s1, char *s2);
int			case_one(t_data *data);
void		*routine(void *args);

#endif
