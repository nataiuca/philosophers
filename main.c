/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:14:40 by natferna          #+#    #+#             */
/*   Updated: 2025/05/16 00:58:46 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_rules		rules;
	t_philo		*ph;
	pthread_t	mon;

	if (init_rules(&rules, ac, av))
		return (1);
	ph = malloc(sizeof(t_philo) * rules.num_philos);
	if (!ph)
		return (write(2, "Error malloc\n", 14), 1);
	if (create_philosophers(&rules, ph))
		return (1);
	pthread_create(&mon, NULL, monitor_routine, ph);
	pthread_join(mon, NULL);
	cleanup(ph, &rules);
	return (0);
}
