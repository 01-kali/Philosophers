/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 05:17:10 by zelkalai          #+#    #+#             */
/*   Updated: 2024/09/09 14:15:55 by zelkalai         ###   ########.fr       */
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

int	check_arg(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
	{
		printf("Error: Invalid argument.\n");
		return (1);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 0)
	{
		printf("Error: Invalid argument.\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philosophers;

	philosophers = NULL;
	if (argc == 6 || argc == 5)
	{
		if (check_arg(argc, argv))
			return (1);
		if (set_data1(&philosophers, &data, argc, argv))
			return (1);
		if (data.number_of_philo == 1)
		{
			printf("%lld 1 has taken a fork\n", get_time() - data.start);
			ft_usleep(data.time_to_die);
			printf("%lld 1 died\n", get_time() - data.start);
			return (dest(&data, philosophers), 0);
		}
		create_philo(&data, philosophers);
		dest(&data, philosophers);
	}
	else
	{
		printf("Error: Invalid argument.\n");
		return (1);
	}
}
