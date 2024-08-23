#ifndef PHILO_BONUS
#define PHILO_BONUS

#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_dat
{
  int number_of_philo;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int number_of_meals;
  long long star;
  int died;
  sem_t death;
  sem_t forks;
};

typedef struct s_philo
{
  int i;
  int pid;
  int number_of_meals_eaten;
  long long last_meal; 
  t_data *data;
};

#endif
