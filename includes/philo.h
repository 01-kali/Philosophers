/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:27:13 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/06 17:27:16 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
# include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

typedef struct s_philo
{
  pthread_t philosopher;
  
} t_philo

#endif
