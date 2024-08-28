/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:51:07 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/28 16:51:09 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	create_philo(t_data *data, t_philo *philosophers)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philo)
		pthread_create(&philosophers[i].philosopher, NULL, philo, \
				&philosophers[i]);
	i = -1;
	while (++i < data->number_of_philo)
		pthread_join(philosophers[i].philosopher, NULL);
}
