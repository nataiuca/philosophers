/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:21:00 by natferna          #+#    #+#             */
/*   Updated: 2025/05/16 01:55:46 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* imprime estado sin mezcla */
void	print_state(t_philo *p, char *msg)
{
	pthread_mutex_lock(&p->rules->print_mutex);
	if (!p->rules->stop)
		printf("%ld %d %s\n", timestamp_ms(p->rules), p->id, msg);
	pthread_mutex_unlock(&p->rules->print_mutex);
}

int	create_philosophers(t_rules *rules, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < rules->num_philos)
	{
		ph[i].id = i + 1;
		ph[i].eat_count = 0;
		ph[i].rules = rules;
		pthread_mutex_init(&ph[i].meal_mutex, NULL);
		pthread_mutex_lock(&ph[i].meal_mutex);
		ph[i].last_meal = timestamp_ms(rules);
		pthread_mutex_unlock(&ph[i].meal_mutex);
		if (pthread_create(&ph[i].thread, NULL, philosopher_routine,
				&ph[i]) != 0)
			return (1);
		pthread_detach(ph[i].thread);
		i++;
	}
	return (0);
}

/* rutina de filósofo */
void	*philosopher_routine(void *arg)
{
	t_philo	*p;
	t_rules	*r;

	p = arg;
	r = p->rules;
	pthread_mutex_lock(&p->meal_mutex);
	p->last_meal = timestamp_ms(p->rules);
	pthread_mutex_unlock(&p->meal_mutex);
	if (p->id % 2 == 1)
		precise_sleep(r->time_to_eat / 2);
	while (!r->stop)
	{
		take_forks(p);
		eat_and_release(p);
		if (r->must_eat_count > 0 && p->eat_count >= r->must_eat_count)
			break ;
		print_state(p, "is sleeping");
		precise_sleep(r->time_to_sleep);
		print_state(p, "is thinking");
	}
	return (NULL);
}
