/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:18:16 by natferna          #+#    #+#             */
/*   Updated: 2025/05/17 01:04:50 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	timestamp_ms(t_rules *r)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - r->start_time.tv_sec) * 1000 + (now.tv_usec
			- r->start_time.tv_usec) / 1000);
}

int	init_values(t_rules *r, int ac, char **av)
{
	r->num_philos = ft_atoi(av[1]);
	r->time_to_die = ft_atol(av[2]);
	r->time_to_eat = ft_atol(av[3]);
	r->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		r->must_eat_count = ft_atoi(av[5]);
	else
		r->must_eat_count = 0;
	if (r->num_philos <= 0 || r->num_philos >= 200)
		return (write(2, "Error: philosophers must be between 1 and 199\n", 46),
			1);
	if (r->time_to_die < 60 || r->time_to_eat < 60 || r->time_to_sleep < 60
		|| r->must_eat_count < 0)
		return (write(2, "Error: invalid argument values\n", 29), 1);
	return (0);
}

int	init_forks(t_rules *r)
{
	int	i;

	r->forks = malloc(sizeof(pthread_mutex_t) * r->num_philos);
	if (!r->forks)
		return (write(2, "Error malloc\n", 14), 1);
	i = 0;
	while (i < r->num_philos)
		pthread_mutex_init(&r->forks[i++], NULL);
	return (0);
}

int	init_rules(t_rules *r, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (write(2, "Error args\n", 11), 1);
	if (init_values(r, ac, av))
		return (1);
	r->stop = 0;
	pthread_mutex_init(&r->print_mutex, NULL);
	if (init_forks(r))
		return (1);
	gettimeofday(&r->start_time, NULL);
	return (0);
}

void	cleanup(t_philo *ph, t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->num_philos)
		pthread_mutex_destroy(&r->forks[i++]);
	free(r->forks);
	pthread_mutex_destroy(&r->print_mutex);
	while (i--)
		pthread_mutex_destroy(&ph[i].meal_mutex);
	free(ph);
}
