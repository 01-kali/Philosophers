/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:38:55 by zelkalai          #+#    #+#             */
/*   Updated: 2024/11/13 02:48:30 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int			number_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_meals;
	long long	start;
	pid_t		*pids;
	sem_t		*forks;
}				t_data;

typedef struct s_philo
{
	int			i;
	pid_t		pid;
	int			number_of_meals_eaten;
	long long	last_meal;
	t_data		*data;
}				t_philo;

void			clean(t_data *data, t_philo *philosophers);
int				main(int argc, char **argv);
void			post_forks(t_data *data);
int				take_forks(t_philo *philosopher, t_data *data, t_philo *ph);
int				eating(t_philo *philosopher, t_data *data, t_philo *ph);
int				check_one_philo(t_data *data, t_philo *philosopher);
void			philo(t_philo *philosopher, t_data *data, t_philo *ph);
long long		get_time(void);
void			ft_usleep(long long time_to_sleep, t_philo *philosopher, \
		t_data *data, t_philo *ph);
void			ft_check(long num, char *str, int len);
char			*ft_itoa(int n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
int				check_death(t_philo *philosopher, t_data *data, t_philo *ph);
int				clean_philo(t_data *data, int i);
int				set_data2(t_philo **philosophers, t_data *data, int argc, \
	char **argv);
int				set_data(t_philo **philosophers, t_data *data, int argc, \
	char **argv);

#endif
