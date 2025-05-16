/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:15:55 by natferna          #+#    #+#             */
/*   Updated: 2025/05/16 01:51:00 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* toma dos tenedores */
void	take_forks(t_philo *p)
{
	int	l;
	int	r;

	l = p->id - 1;
	r = p->id % p->rules->num_philos;
	pthread_mutex_lock(&p->rules->forks[l]);
	print_state(p, "has taken a fork");
	pthread_mutex_lock(&p->rules->forks[r]);
	print_state(p, "has taken a fork");
}

/* come y libera tenedores con mutex en last_meal */
void	eat_and_release(t_philo *p)
{
	t_rules	*r;

	r = p->rules;
	pthread_mutex_lock(&p->meal_mutex);
	print_state(p, "is eating");
	p->last_meal = timestamp_ms(p->rules);
	pthread_mutex_unlock(&p->meal_mutex);
	precise_sleep(r->time_to_eat);
	p->eat_count++;
	pthread_mutex_unlock(&r->forks[p->id % r->num_philos]);
	pthread_mutex_unlock(&r->forks[p->id - 1]);
}
