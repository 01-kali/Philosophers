/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 05:17:10 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/23 05:49:30 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	dest(t_data *data, t_philo *philosophers)
{
	int	i;

	i = -1;
	while (++i < (*data).number_of_philo)
		pthread_mutex_destroy(&(*data).forks[i]);
	pthread_mutex_destroy(&(*data).death);
	free((*data).forks);
	free(philosophers);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philosophers;

	philosophers = NULL;
	if ((argc == 6 && ft_atoi(argv[5]) < 0) || argc < 5 || argc > 6
		|| ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
	{
		printf("Error.\n");
		return (1);
	}
	set_data1(&philosophers, &data, argc, argv);
	if (data.number_of_philo == 1)
	{
		printf("%lld 1 has taken a fork\n", get_time() - data.start);
		ft_usleep(data.time_to_die);
		printf("%lld 1 died\n", get_time() - data.start);
		free(data.forks);
		free(philosophers);
		return (0);
	}
	create_philo(&data, philosophers);
	dest(&data, philosophers);
}
