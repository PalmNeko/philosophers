/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_order.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:49:33 by tookuyam          #+#    #+#             */
/*   Updated: 2025/03/08 15:49:52 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_types.h"
#include <pthread.h>
#include <unistd.h>

int	ph_order(t_philosopher *philo, t_philo_action action, bool is_lock)
{
	if (is_lock)
		pthread_mutex_lock(&philo->lock);
	philo->ordered_action = action;
	philo->status = PH_HAS_ORDER;
	if (is_lock)
		pthread_mutex_unlock(&philo->lock);
	return (0);
}

int	ph_wait_some_order(t_philosopher *philo)
{
	t_philo_action	action;

	action = PH_ACT_NONE;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->status == PH_HAS_ORDER || philo->in_process == false)
		{
			pthread_mutex_unlock(&philo->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->lock);
		usleep(0);
	}
	return (0);
}

int	ph_to_status(t_philosopher *philo, t_philo_status status)
{
	pthread_mutex_lock(&philo->lock);
	philo->status = status;
	pthread_mutex_unlock(&philo->lock);
	return (0);
}
