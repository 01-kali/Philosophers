/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:26:56 by zelkalai          #+#    #+#             */
/*   Updated: 2024/08/06 17:26:58 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void *philo(void* arg)
{
  (void)arg;
  return(NULL);
}

pthread_t creat_philo()
{
  pthread_t philo;
  return(philo);
}

int main(int argc, char **argv)
{
  pthread_t *philosopher;
  int i;
  int n_p;

  i = -1;
  if(argc == 5)
  {
    n_p = ft_atoi(argv[1]);
    while(++i < n_p)
    {
      philosopher[i] = 
      pthread_create(&creat_philo,NULL,philo, NULL);
    }
    i = -1;
    while (++i < n_p)
      pthread_join(philosopher, NULL);
  }
  else if(argc == 6)
  {
    
  }
  else
  {
    printf("error, check the number of arguments.\n");
    return(1);
  }
}
