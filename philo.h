#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int time_has_fork;
	int time_is_eating;
	int time_is_sleeping;
	int time_is_thinking;
	int time_is_dead;
	pthread_t	thread_philo;
}		t_philo;

typedef struct s_scene
{
	int 	nb_philo;
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int 	nb_eat;
	t_philo	*philo;
	pthread_t thread_scene;
}			t_scene;

int ft_strlen(const char *str);
int	ft_atoi(const char *str);

t_scene *init(int argc, char **argv);

#endif