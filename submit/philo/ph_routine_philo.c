/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:18:58 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/13 17:18:58 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

bool	ph_isdone(t_philosopher *philo);
void	ph_done(t_philosopher *philo);

void	*ph_routine_philo(t_philosopher *philo)
{
	int		cnt;
	// bool	in_process;

	cnt = 0;
	while (philo->manager->config->must_eat_times == -1
		|| philo->eat_cnt < philo->manager->config->must_eat_times)
	{
		ph_wait_some_order(philo);
		if (philo->ordered_action == PH_DIE)
			return (ph_run_die(philo), NULL);
		if (philo->ordered_action == PH_EAT)
			ph_run_eat(philo);
		else if (philo->ordered_action == PH_SLEEP)
			ph_run_sleep(philo);
		else if (philo->ordered_action == PH_THINK)
			ph_run_think(philo);
		if (ph_isdone(philo))
			return (NULL);
	}
	ph_print_action(philo, PH_SLEEP);
	ph_done(philo);
	return (NULL);
}

void	ph_done(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->status = PH_DONE;
	pthread_mutex_unlock(&philo->lock);
}

bool	ph_isdone(t_philosopher *philo)
{
	bool	done;

	pthread_mutex_lock(&philo->lock);
	done = philo->in_process == false;
	pthread_mutex_unlock(&philo->lock);
	return (done);
}
