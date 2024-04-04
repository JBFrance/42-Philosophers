/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrances <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:15:51 by jfrances          #+#    #+#             */
/*   Updated: 2023/07/28 14:34:58 by jfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define MAX_LONG 922337203685477580
# define UNLOCK 1
# define LOCK 0

struct	s_monitor;

typedef struct s_philo
{
	int					eaten;
	int					index;
	char				*index_str;
	int					r_fork;
	int					l_fork;
	unsigned long		last_ate;
	struct s_monitor	*monitor;
	pthread_t			track;
	pthread_mutex_t		la_ate_mutex;
}				t_philo;

typedef struct s_monitor
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count_max;
	int				eat_lim;
	int				stop_condition;
	unsigned long	start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	to_write;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	e_lst_mutex;
	pthread_mutex_t	eat_lim_mutex;
	pthread_mutex_t	c_max_mutex;
	pthread_mutex_t	count_mutex;
}				t_monitor;

typedef struct s_helper
{
	int	count_help;
	int	max_help;
}				t_helper;

int				threads_init(t_monitor *monitor);
int				initialize(t_monitor *monitor);
int				parsing(t_monitor *monitor, int argc, char *argv[], int i);
int				ft_error(char *msg);
int				ft_isint(const char *str);
int				ft_atoi(const char *str);
unsigned long	get_time(void);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_itoa(int n);
void			my_slp(unsigned long duration, t_monitor *monitor);
void			writing(char *msg, t_philo *philo);
void			eating(t_philo *philo);
void			is_dead(t_monitor *monitor, t_philo *philo);
#endif
