#include <philo_bonus.h>

long long get_time(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void ft_usleep(long long time_to_sleep)
{
    long long start_time = get_time();
    while (get_time() - start_time < time_to_sleep)
        usleep(time_to_sleep / 10);
}

int check_death(t_philo *philosopher, t_data *data)
{
  int i;

  sem_wait(data->death);
  if (get_time() - philosopher->last_meal > data->time_to_die)
  {
    usleep(2);
    if(philosopher->i + 1 > 2)
    {
      sem_post(data->death);
      ft_usleep(1);
      sem_wait(data->death);
    }
    printf("%lld %d died\n", get_time() - data->start, philosopher->i + 1);
    i = -1;
    data->died = 1;
    sem_post(data->death);
    exit(1);
  }
  sem_post(data->death);
  return (0);
}

int ft_atoi(const char *str)
{
  int r;
  int s;
  
  r = 0;
  s = 1;
  while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n'
      || *str == '\r' || *str == '\f')
      str++;
  if(*str == '\0')
    return(-1);
  if (*str == '-' || *str == '+')
  {
      if (*str == '-')
          s = -1;
      str++;
  }
  while (*str && *str >= '0' && *str <= '9')
  {
      r = r * 10 + (*str - '0');
      str++;
  }
  if(*str && *str != ' ' && (*str < '0' || *str > '9'))
    return(-1);
  while(*str && (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n'
      || *str == '\r' || *str == '\f'))
    str++;
  if(*str != '\0')
    return(-1);
  return ((int)r * s);
}

void post_forks(t_data *data)
{
  sem_post(data->forks);
  sem_post(data->forks);
}

int take_forks(t_philo *philosopher, t_data *data)
{
  if ((philosopher->i + 1) % 2 == 1)
      usleep(600);
  sem_wait(data->forks);
  if (check_death(philosopher, data))
  {
      sem_post(data->forks);
      return (1);
  }
  printf("%lld %d has taken a fork\n", get_time() - data->start, philosopher->i + 1);
  sem_wait(data->forks);
  if (check_death(philosopher, data))
  {
      post_forks(data);
      return (1);
  }
  printf("%lld %d has taken a fork\n", get_time() - data->start, philosopher->i + 1);
  return (0);
}

int eating(t_philo *philosopher, t_data *data)
{
  if (take_forks(philosopher, data))
      return (1);
  if (check_death(philosopher, data))
  {
      post_forks(data);
      return (1);
  }
  philosopher->last_meal = get_time();
  printf("%lld %d is eating\n", get_time() - data->start, philosopher->i + 1);
  ft_usleep(data->time_to_eat);
  post_forks(data);
  philosopher->number_of_meals_eaten++;
  if (check_death(philosopher, data))
      return (1);
  return (0);
}

void philo(t_philo *philosopher, t_data *data)
{
  if (data->number_of_philo == 1)
  {
      printf("%lld 1 has taken a fork\n", get_time() - data->start);
      ft_usleep(data->time_to_die);
      printf("%lld 1 died\n", get_time() - data->start);
      return;
  }
  while (1)
  {
      if (eating(philosopher, data))
          break;
      if (data->number_of_meals != -1 && philosopher->number_of_meals_eaten >= data->number_of_meals)
          break;
      printf("%lld %d is sleeping\n", get_time() - data->start, philosopher->i + 1);
      ft_usleep(data->time_to_sleep);
      if (check_death(philosopher, data))
          break;
      printf("%lld %d is thinking\n", get_time() - data->start, philosopher->i + 1);
      usleep(200);
  }
}

void set_data(t_philo **philosophers, t_data *data, int argc, char **argv)
{
  int i;

  data->number_of_philo = ft_atoi(argv[1]);
  data->time_to_die = ft_atoi(argv[2]);
  data->time_to_eat = ft_atoi(argv[3]);
  data->time_to_sleep = ft_atoi(argv[4]);
  if (argc == 6)
      data->number_of_meals = ft_atoi(argv[5]);
  else
      data->number_of_meals = -1;
  data->start = get_time();
  data->died = 0;
  data->pids = (pid_t *)malloc(sizeof(pid_t) * data->number_of_philo);
  sem_unlink("/death");
  data->death = sem_open("/death", O_CREAT, 0644, 1);
  sem_unlink("/forks");
  data->forks = sem_open("/forks", O_CREAT, 0644, data->number_of_philo);
  if (data->forks == SEM_FAILED || data->death == SEM_FAILED)
  {
      perror("sem_open failed");
      exit(0);
  }
  *philosophers = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
  i = -1;
  while (++i < data->number_of_philo)
  {
      (*philosophers)[i].i = i;
      (*philosophers)[i].number_of_meals_eaten = 0;
      (*philosophers)[i].last_meal = get_time();
      (*philosophers)[i].data = data;
      (*philosophers)[i].pid = fork();
      if ((*philosophers)[i].pid == 0)
      {
          philo(&(*philosophers)[i], data);
          exit(0);
      }
      else if ((*philosophers)[i].pid > 0)
          data->pids[i] = (*philosophers)[i].pid;
      else
          exit(1);
  }
}

void clean(t_data *data, t_philo *philosophers)
{
  pid_t pid;
  int status;
  int i;

  i = -1;
  while(++i < data->number_of_philo)
  {
    pid = waitpid(-1, &status, 0);
    if(status != 0)
    {
      i = -1;
      while(++i < data->number_of_philo)
        kill(data->pids[i], SIGKILL);
      break;
    }
  }
  sem_close(data->death);
  sem_close(data->forks);
  sem_unlink("/death");
  sem_unlink("/forks");
  free(philosophers);
  free(data->pids);
}

int main(int argc, char **argv)
{
  t_data data;
  t_philo *philosophers;

  if(argc == 6 || argc == 5)
  {
    if ( ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
      || ft_atoi(argv[4]) < 0)
    {
      printf("Error: Invalid argument.\n");
      return (1);
    }
    if(argc == 6 && ft_atoi(argv[5]) < 0)
    {
      printf("Error: Invalid argument.\n");
      return (1);
    }
    set_data(&philosophers, &data, argc, argv);
    clean(&data, philosophers);
  }
  else
  {
    printf("Error: Invalid argument.\n");
    return (1);
  }
  return (0);
}
