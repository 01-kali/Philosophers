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
      threads[i] = 
      pthread_create(&philosopher[i],NULL,philo, NULL);
    }
    i = -1;
    while (++i < np)
      pthread_join(philosopher[i], NULL);
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
