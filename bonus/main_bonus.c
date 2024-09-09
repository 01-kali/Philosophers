/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:38:09 by zelkalai          #+#    #+#             */
/*   Updated: 2024/09/09 14:11:16 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	clean(t_data *data, t_philo *philosophers)
{
	int	status;
	int	i;

	i = -1;
	while (++i < data->number_of_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < data->number_of_philo)
				kill(data->pids[i], SIGKILL);
			break ;
		}
	}
	sem_close(data->death);
	sem_close(data->forks);
	sem_unlink("/death");
	sem_unlink("/forks");
	free(philosophers);
	free(data->pids);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philosophers;

	if (argc == 6 || argc == 5)
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
		if (set_data(&philosophers, &data, argc, argv))
			return (1);
		clean(&data, philosophers);
	}
	else
	{
		printf("Error: Invalid argument.\n");
		return (1);
	}
}
