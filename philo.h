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
	int				eaten; //quante volte mangia
	int				eating; //per sapere se sta mangiando o meno
	u_int64_t		last_eat; //ultimo orario in cui ha mangiato
	u_int64_t		t_die; //tempo che deve passare da last_eat prima che muoia
	pthread_mutex_t	*l_fork; //forchetta sinistra
	pthread_mutex_t	*r_fork; //forchetta destra
	pthread_mutex_t	lock; //mutex che implica che sta mangiando
	pthread_t		monitor_id; //monitor associato al filosofo
}	t_philo;

typedef struct s_data
{
	int					n_philo; //numero di philo
	u_int64_t			t_die; //tempo alla morte (presente anche in t_philo)
	u_int64_t			t_eat; //tempo che deve impiegare a mangiare
	u_int64_t			t_sleep; //tempo che deve impiegare a dormire
	u_int64_t			start_time; //ora di inizio del programma
	int					n_eat; //numero di volte che deve mangiare un filosofo
	int					dead; //variabile di stato per definire se un filosofo e' morto
	int					finished;
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

#endif
