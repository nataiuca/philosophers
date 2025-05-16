/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:18:57 by natferna          #+#    #+#             */
/*   Updated: 2025/05/16 01:31:54 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *ph, t_rules *r)
{
	int		i;
	long	dt;

	i = 0;
	while (i < r->num_philos)
	{
		pthread_mutex_lock(&ph[i].meal_mutex);
		dt = timestamp_ms(r) - ph[i].last_meal;
		if (dt > r->time_to_die)
		{
			print_state(&ph[i], "died");
			pthread_mutex_unlock(&ph[i].meal_mutex);
			r->stop = 1;
			return (1);
		}
		pthread_mutex_unlock(&ph[i].meal_mutex);
		i++;
	}
	return (0);
}

int	check_full(t_philo *ph, t_rules *r)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (i < r->num_philos)
	{
		pthread_mutex_lock(&ph[i].meal_mutex);
		if (ph[i].eat_count >= r->must_eat_count)
			done++;
		pthread_mutex_unlock(&ph[i].meal_mutex);
		i++;
	}
	if (done == r->num_philos)
	{
		r->stop = 1;
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*ph;
	t_rules	*r;

	ph = arg;
	r = ph[0].rules;
	while (!r->stop)
	{
		if (check_death(ph, r))
			break ;
		if (r->must_eat_count > 0 && check_full(ph, r))
			break ;
		usleep(1000);
	}
	return (NULL);
}
