#ifndef PHILO_BONUS
#define PHILO_BONUS

#include <semaphore.h>
# include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
  int number_of_philo;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int number_of_meals;
  long long start;
  int died;
  sem_t death;
  sem_t forks;
} t_data;

typedef struct s_philo
{
  int i;
  pid_t pid;
  int number_of_meals_eaten;
  long long last_meal; 
  t_data *data;
} t_philo;

#endif
