#include "philo.h"

void	*ft_time_scene(t_scene *scene)
{
	int i = 0;
	while (i++ < scene->nb_philo)
	{
		printf("time to eat du philo %d vaut %d\n",scene->nb_philo - 1, scene->philo[scene->nb_philo - 1].time_is_eating);
		if (scene->philo[scene->nb_philo - 1].time_is_eating == scene->nb_eat)
		{
			printf("tout le monde a mange\n");
		}
	}
	return (NULL);
}

void 	*ft_time_philo(t_philo *philo)
{
	int j = 0;
	while (j++ < 20)
	{
		printf("philo [%d] a manger %d de fois\n", philo->index, philo->time_is_eating);
		philo->time_is_eating++;
	}
	return (NULL) ;
}

int main(int argc, char **argv)
{
	t_scene *scene;
	int i;
	int ret;

	i = 0;
	ret = 0;

	if (argc != 5 && argc != 6)
		return (-1);
	scene = init(argc, argv);
	printf("creation du thread de la scene ! \n");
	ret = pthread_create(&scene->thread_scene, NULL, ft_time_scene(scene), NULL);

	while ( i < scene->nb_philo)
	{
		printf("creation du thread philo %d! \n", i);
		ret = pthread_create(&scene->philo[i].thread_philo, NULL, ft_time_philo(&scene->philo[i]), NULL);
		i++;
	}
	return (0);
}