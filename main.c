#include "philo.h"

int 	ft_time_scene(t_scene *scene)
{
	return ;
}

int 	ft_time_philo(t_scene *scene)
{
	return ;
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
	ret = pthread_create(&scene->thread_scene, NULL, &ft_time_scene(), scene);
	if (ret)
	{
		printf("creation du thread philo ! \n");
		while ( i < scene->nb_philo)
		{
			ret = pthread_create(&scene->philo[i].thread_philo, NULL, &ft_time_philo(), scene)
			i++;
		}
	}
//	while (scene->nb_philo--)
//		printf("coucou philo[%d] %d\n",scene->nb_philo, scene->philo[scene->nb_philo].time_is_thinking);
	return (0);
}