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

void	ph_order_to_philos(t_manager *manager);
void	ph_order_action(t_philosopher *philo);
void	ph_exit_all_philo(t_manager *manager);
void	ph_to_next_target(t_manager *manager);

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
		ph_order_to_philos(manager);
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

void	ph_order_to_philos(t_manager *manager)
{
	int	index;

	index = 0;
	while (index < manager->config->philo_cnt)
	{
		ph_order_action(&manager->philos[index]);
		index++;
	}
	return ;
}

void	ph_order_action(t_philosopher *philo)
{
	t_manager	*manager;

	manager = philo->manager;
	pthread_mutex_lock(&philo->lock);
	if (philo->status == PH_HAS_ORDER)
		;
	else if (philo->ordered_action == PH_NONE)
		ph_order(philo, PH_THINK, false);
	else if (ph_can_eat(philo))
		ph_order(philo, PH_EAT, false);
	else if (philo->ordered_action == PH_EAT)
	{
		ph_to_next_target(manager);
		ph_order(philo, PH_SLEEP, false);
	}
	else if (philo->ordered_action == PH_SLEEP)
		ph_order(philo, PH_THINK, false);
	pthread_mutex_unlock(&philo->lock);
}

void	ph_to_next_target(t_manager *manager)
{
	manager->target_no += 2;
	if (manager->target_no >= manager->config->philo_cnt)
		manager->target_no = (manager->target_no + 1) % 2;
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
