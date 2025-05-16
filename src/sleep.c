/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:17:12 by natferna          #+#    #+#             */
/*   Updated: 2025/05/16 01:57:51 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	precise_sleep(long ms)
{
	struct timeval	start;
	struct timeval	now;

	gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	while ((now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - start.tv_usec)
		/ 1000 < ms)
	{
		usleep(500);
		gettimeofday(&now, NULL);
	}
}
