#include "philo.h"

int init_philo(t_scene *scene)
{
	int i;

	i = 0;
	scene->philo = (t_philo *)malloc(sizeof(t_philo) * scene->nb_philo);
	if (!scene->philo)
		return (-1);
	while (i < scene->nb_philo)
	{
		scene->philo[i].time_has_fork = 0;
		scene->philo[i].time_is_eating = 0;
		scene->philo[i].time_is_sleeping = 0;
		scene->philo[i].time_is_thinking = 0;
		scene->philo[i].time_is_dead = 0;
		i++;
	}
	return (0);
}

t_scene *init_scene(int argc, char **argv)
{
	t_scene *scene;

	scene = (t_scene *)malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->nb_philo = ft_atoi(argv[1]);
	scene->time_to_die = ft_atoi(argv[2]);
	scene->time_to_eat = ft_atoi(argv[3]);
	scene->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		scene->nb_eat = ft_atoi(argv[5]);
	else
		scene->nb_eat = 0;
	if (init_philo(scene))
		return (NULL);
	return (scene);
}

t_scene *init(int argc, char **argv)
{
	t_scene *scene;
	scene = init_scene(argc, argv);
	if (!scene)
		return (NULL);
	return (scene);
}