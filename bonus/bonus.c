#include <philo_bonus.h>

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long time_to_sleep)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_to_sleep)
		usleep(time_to_sleep / 10);
}

int check_death(t_philo **philosophers, t_data *data)
{
	if (data->died == 1)
	{
		return (1);
	}
	if (get_time() - philosopher->last_meal >= data->time_to_die)
	{
		printf("%lld %d died\n", get_time() - data->start, philosopher->i + 1);
		data->died = 1;
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	r;
	int	s;

	r = 0;
	s = 1;
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n'
		|| *str == '\r' || *str == '\f')
		str++;
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
	return ((int)r * s);
}

int take_forkes(t_philo **philosophers, t_data *data)
{
  if(((*philosophers)->i + 1) % 2 == 1)
  {
    ft_usleep(1);
    if(check_death(philosophers, data))
      return(1);
    printf("%lld %d has taken a fork\n", get_time() - data->start, (*philosophers)->i + 1);
    printf("%lld %d has taken a fork\n", get_time() - data->start, (*philosophers)->i + 1);
    
  }
  else
  {
    if(check_death(philosophers, data))
      return(1);
    printf("%lld %d has taken a fork\n", get_time() - data->start, (*philosophers)->i + 1);
    printf("%lld %d has taken a fork\n", get_time() - data->start, (*philosophers)->i + 1);
  }
}

int eating(t_philo **philosophers, t_data *data)
{
  if(take_forkes(philosophers, data))
    return(1);
  (*philosophers)->last_meal = get_time();
  printf("%lld %d is eating\n", get_time() - data->start, (*philosophers)->i + 1);
  ft_usleep(time_to_eat);
  (*philosophers)->number_of_meals_eaten++;
  if(check_death(philosophers, data))
    return(1)
  return(0);
}

void philo(t_philo **philosophers, t_data *data)
{
  while(1)
  {
    if(eating(philosophers, data))
      break;
    if(data->number_of_meals != -1 && (*philosophers)->number_of_meals_eaten >= data->number_of_meals)
      break;
    printf("%lld %d is sleeping\n", get_time() - data->start, (*philosophers)->i + 1);
    ft_usleep(data->time_to_sleep);
    if(check_death(philosophers, data))
      break;
    printf("%lld %d is thinking\n", get_time() - data->start, (*philosophers)->i + 1);
  }
}
void set_data(t_philo **philosophers, t_data *data, int argc, char **argv)
{
  int i;
  
  data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
  if(argc == 6)
	  data->number_of_meals = ft_atoi(argv[5]);
  else
    data->number_of_meals = -1;
  data->start = get_time();
  data->died = 0;
  data->death = sem_open("/death", O_CREAT, 1);
  data->forks = sem_open("/forks", O_CREAT, data->number_of_philo);
  if(data->forks == SEM_FAILED || data->death == SEM_FAILED)
    exit(1);
  philosophers = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philo);
  i = -1;
  while(++i < data->number_of_philo)
  {
    (*philosophers)[i].i = i;
    (*philosophers)[i].number_of_meals_eaten = 0;
    (*philosophers)[i].last_meal = 0;
    (*philosophers)[i].data = data;
    (*philosophers)[i].pid = fork();
    if((*philosophers)[i].pid == 0)
        philo(philosophers, data);
    else if (pid < 0)
        exit(1);
  }
}

int main(int argc, char **argv)
{
  t_data data;
  t_philo *philosophers;
  
  if ((argc == 6 && ft_atoi(argv[5]) < 0) || argc < 5 || argc > 6
		|| ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0
		|| ft_atoi(argv[4]) < 0)
	{
		printf("Error.\n");
		return (1);
	}
  set_data(&philosophers, &data, argc, argv);
  while(1);
  return(0);
}
