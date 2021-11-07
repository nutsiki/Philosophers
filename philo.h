#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_scene	t_scene;

typedef struct s_philo
{
	unsigned long long	time_has_fork;
	unsigned long long	time_is_eating;
	unsigned long long	time_is_sleeping;
	unsigned long long	time_is_thinking;
	int					time_is_dead;
	int					is_eating;
	int					nb_eat;
	int					index;
	unsigned long long	last_eat;
	unsigned long long	new_eat;
	pthread_t			thread_philo;
	t_scene				*scene;
	pthread_mutex_t		*forks_left;
	pthread_mutex_t		*forks_right;
}						t_philo;

typedef struct s_scene
{
	int					nb_philo;
	unsigned long long 	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	start;
	int					nb_eat_max;
	int					death;
	t_philo				*philo;
	pthread_t			thread_scene;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print;
}						t_scene;

int ft_strlen(const char *str);
int	ft_atoi(const char *str);
time_t	get_time(void);

t_scene *init(int argc, char **argv);

#endif