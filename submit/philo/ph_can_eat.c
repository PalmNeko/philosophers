/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_can_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:32:49 by tookuyam          #+#    #+#             */
/*   Updated: 2025/03/08 16:49:22 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

bool	ph_can_eat(t_philosopher *philo)
{
	t_philosopher	*next_philo;
	t_manager		*manager;

	manager = philo->manager;
	next_philo = ph_get_next_philo(philo);
	if (philo->ordered_action == PH_THINK
		&& philo->no != next_philo->no
		&& next_philo->ordered_action != PH_EAT
		&& manager->target_no == philo->no - 1)
		return (true);
	return (false);
}
