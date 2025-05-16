/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natferna <natferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:11:41 by natferna          #+#    #+#             */
/*   Updated: 2025/05/16 01:29:03 by natferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdint.h>

typedef struct s_rules
{
    int             num_philos;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             must_eat_count;
    int             stop;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
    struct timeval  start_time;
}               t_rules;

typedef struct s_philo
{
    int             id;
    int             eat_count;
    long  last_meal;
    pthread_mutex_t meal_mutex;
    t_rules         *rules;
    pthread_t       thread;
}               t_philo;

long timestamp_ms(t_rules *r);
void precise_sleep(long ms);
void print_state(t_philo *p, char *msg);
void take_forks(t_philo *p);
void eat_and_release(t_philo *p);
void *philosopher_routine(void *arg);
int check_death(t_philo *ph, t_rules *r);
int check_full(t_philo *ph, t_rules *r);
void *monitor_routine(void *arg);
int	init_values(t_rules *r, int ac, char **av);
int	init_forks(t_rules *r);
int init_rules(t_rules *r, int ac, char **av);
void cleanup(t_philo *ph, t_rules *r);
int create_philosophers(t_rules *rules, t_philo *ph);

#endif