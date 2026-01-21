# philosophers

hey, this is my project for the philosophers assignment. basically its a simulation of the dining philosophers problem where they sit at a table and have to eat, sleep and think without dying of starvation.

i did both the mandatory part (threads and mutexes) and the bonus part (processes and semaphores).

## how to compile
its pretty easy, i made a makefile for everything.

to get the standard version with threads:
```bash
make
```
if u want the bonus version with processes:
```bash
make bonus
```
if u want to clean everything just run `make fclean`.

## how to run it

you need to give it specific argumets to work. here is the format:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
same thing for the bonus:
```bash
./philo_bonus 5 800 200 200
```

## arguments explanation:

1. number_of_philosophers: the number of philos and also the number of forks.
 
2. time_to_die: time in ms. if a philo doesnt start eating 'time_to_die' ms after starting his last meal, he dies.
 
3. time_to_eat: time it takes to eat. usually they need two forks.
 
4. time_to_sleep: time they spend sleeping.
 
5. number_of_times_each_philosopher_must_eat: (optional) simulation stops if all philos have eaten at least this many times.

## about the code

- mandatory: i used pthread functions and mutexes to protect the forks. the main logic is in the utils folder.
 
- bonus: here i used fork() to create processes and semaphores for the forks. main logic is in the bonus folder.
