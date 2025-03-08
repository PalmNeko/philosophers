/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine_update_manager.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:14:13 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/15 17:14:13 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <sys/time.h>
#include <unistd.h>

void	ph_update_philo_eating(t_manager *manager);
void	ph_exit_all_philo(t_manager *manager);

void	*ph_routine_update_manager(t_manager *manager)
{
	bool	in_progress;

	manager->target_no = 0;
	while (1)
	{
		pthread_mutex_lock(&manager->lock);
		in_progress = manager->in_process;
		pthread_mutex_unlock(&manager->lock);
		if (in_progress == false)
			break ;
		ph_update_philo_eating(manager);
		if (usleep(0) == -1)
		{
			pthread_mutex_lock(&manager->lock);
			manager->in_process = false;
			pthread_mutex_unlock(&manager->lock);
			break ;
		}
	}
	ph_exit_all_philo(manager);
	return (NULL);
}

void	ph_update_philo_eating(t_manager *manager)
{
	t_philosopher	*target;
	t_philosopher	*next_philo;

	target = &manager->philos[manager->target_no];
	next_philo = &manager->philos[(manager->target_no + 1) % 2];
	pthread_mutex_lock(&target->lock);
	if (target->status == PH_HAS_ORDER)
		;
	else if (target->ordered_action == PH_NONE)
		ph_order(target, PH_THINK, false);
	else if (target->ordered_action == PH_THINK
		&& next_philo->ordered_action != PH_EAT)
		ph_order(target, PH_EAT, false);
	else if (target->ordered_action == PH_EAT)
	{
		manager->target_no += 2;
		if (manager->target_no >= manager->config->philo_cnt)
			manager->target_no = (manager->target_no + 1) % 2;
		ph_order(target, PH_SLEEP, false);
	}
	else if (target->ordered_action == PH_SLEEP)
		ph_order(target, PH_THINK, false);
	pthread_mutex_unlock(&target->lock);
}

void	ph_exit_all_philo(t_manager *manager)
{
	t_philosopher	*target;
	int				index;

	index = 0;
	while (index < manager->config->philo_cnt)
	{
		target = &manager->philos[index];
		pthread_mutex_lock(&target->lock);
		target->in_process = false;
		pthread_mutex_unlock(&target->lock);
		index++;
	}
}
