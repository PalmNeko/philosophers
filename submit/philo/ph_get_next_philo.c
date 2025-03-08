/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_get_next_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:22:44 by tookuyam          #+#    #+#             */
/*   Updated: 2025/03/08 16:23:27 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

t_philosopher	*ph_get_next_philo(t_philosopher *philo)
{
	t_manager	*manager;
	int			no;

	manager = philo->manager;
	no = philo->no - 1;
	return (&manager->philos[(no + 1) % manager->config->philo_cnt]);
}
