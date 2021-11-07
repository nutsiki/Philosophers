#include "philo.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_print(t_philo *philo, unsigned long long time, char *str)
{
	if (!philo->scene->death)
	{
		pthread_mutex_lock(philo->scene->print);
		printf("%llu %d %s",time - philo->scene->start, philo->index, str);
		pthread_mutex_unlock(philo->scene->print);
	}
}


void ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->forks_left);
	pthread_mutex_lock(philo->forks_right);
	philo->time_has_fork = get_time();
	if (!philo->scene->death)
	{
		pthread_mutex_lock(philo->scene->print);
		ft_print(philo, philo->time_has_fork,"%llu %d has taken a fork\n");
		pthread_mutex_unlock(philo->scene->print);
	}
	if (!philo->scene->death) {
		pthread_mutex_lock(philo->scene->print);
		printf("%llu %d has taken a fork\n",philo->time_has_fork - philo->scene->start, philo->index);
		pthread_mutex_unlock(philo->scene->print);
	}
	if (!philo->scene->death) {
		pthread_mutex_lock(philo->scene->print);
		printf("%llu %d is eating\n",get_time() - philo->scene->start, philo->index);
		pthread_mutex_unlock(philo->scene->print);
	}
	philo->is_eating = 1;
	philo->new_eat = get_time();
	usleep(philo->scene->time_to_eat);
	philo->last_eat = philo->new_eat;
	philo->is_eating = 0;
	philo->nb_eat++;
	pthread_mutex_unlock(philo->forks_left);
	pthread_mutex_unlock(philo->forks_right);
	return ;
}

void ft_routine(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (!philo->scene->death)
	{
		ft_philo_eat(philo);
		if (philo->scene->death || philo->nb_eat == philo->scene->nb_eat_max)
			return ;
		pthread_mutex_lock(philo->scene->print);
		printf("%llu %d is sleeping\n", get_time() - philo->scene->start, philo->index);
		pthread_mutex_unlock(philo->scene->print);
		usleep(philo->scene->time_to_sleep);
		philo->time_is_thinking = get_time();
		if (!philo->scene->death) {
			pthread_mutex_lock(philo->scene->print);
			printf("%llu %d is thinking\n", philo->time_is_thinking - philo->scene->start, philo->index);
			pthread_mutex_unlock(philo->scene->print);
		}
	}
	return ;
}

int	check_die(t_philo philo)
{
	if (philo.scene->time_to_die < (get_time()) - philo.last_eat)
	{
		return (1);
	}
	return (0);
}

int ft_eat_enough(t_scene *scene)
{
	int i;

	i = -1;
	if (scene->nb_eat_max < 0)
		return (1);
	while (++i < scene->nb_philo)
		if (scene->philo[i].nb_eat < scene->nb_eat_max)
			return (1);
	return (0);
}

void check_death(void *args)
{
	t_scene *scene;
	int i;

	scene = (t_scene *) args;
	while (ft_eat_enough(scene))
	{
		i = -1;
		while (++i < scene->nb_philo && scene->nb_eat_max != scene->philo[i]. nb_eat)
		{
			if (!scene->philo[i].is_eating && check_die(scene->philo[i]))
			{
				scene->death = 1;
				printf("%llu %d died\n", get_time() - scene->start, scene->philo[i].index);
				return ;
			}
		}
	}
}

void ft_free(t_scene *scene)
{
	int i;

	i = -1;
	while (++i < scene->nb_philo)
		pthread_mutex_destroy(&scene->forks[i]);
	pthread_mutex_destroy(scene->print);
	free(scene->print);
	free(scene->philo);
	free(scene->forks);
	free(scene);
	return ;
}

int main(int argc, char **argv)
{
	t_scene *scene;
	int i;

	i = -1;
	if (argc != 5 && argc != 6)
		return (-1);
	scene = init(argc, argv);
	if (!scene)
		return (-1);
	if (scene->nb_philo == 1)
	{
		printf("%d %d has taken a fork\n", 0, 1);
		usleep(1000 * scene->time_to_die);
		printf("%llu %d died\n", scene->time_to_die + 1, 1);
		return (1);
	}
	else if (scene->nb_philo < 2)
		return (1);
	while ( ++i < scene->nb_philo)
	{
		if (i % 2)
			usleep(100);
		if (pthread_create(&scene->philo[i].thread_philo, NULL, (void *)ft_routine, &scene->philo[i]))
			write(2, "ERROR TH1", 5);
	}
	if (pthread_create(&scene->thread_scene, NULL, (void *)check_death, scene))
		write(2, "ERROR TH2", 5);
	pthread_join(scene->thread_scene, NULL);
	i = -1;
	while (++i < scene->nb_philo)
		pthread_join(scene->philo[i].thread_philo, NULL);
	ft_free(scene);
	return (0);
}