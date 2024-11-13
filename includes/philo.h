/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:27:13 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/13 02:45:06 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long long		start;
	int				died;
	pthread_mutex_t	death;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int				i;
	pthread_t		philosopher;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				number_of_meals_eaten;
	long long		last_meal;
	t_data			*data;
}					t_philo;

int					take_forks2(t_philo *philosopher);
int					take_forks1(t_philo *philosopher);
long long			get_time(void);
void				ft_usleep(long long time_to_sleep, t_philo *philosopher);
void				unlock_forks(t_philo *philosopher);
int					take_forks0(t_philo *philosopher);
int					eating(t_philo *philosopher);
int					check_one_philo(t_data *data, t_philo *philosopher);
int					zzz(t_data *data, t_philo *philosopher);
void				*philo(void *arg);
int					check_death(t_philo *philosopher);
int					set_data2(t_data *data, int argc, char **argv);
int					set_data1(t_philo **philosophers, t_data *data, int argc,
						char **argv);
void				dest(t_data *data, t_philo *philosophers);
int					check_arg(int argc, char **argv);
int					main(int argc, char **argv);
void				create_philo(t_data *data, t_philo *philosophers);
void				ft_check(long num, char *str, int len);
char				*ft_itoa(int n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(const char *s);
int					ft_atoi(const char *str);

#endif
