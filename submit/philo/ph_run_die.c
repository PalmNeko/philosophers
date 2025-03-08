/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_die.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:25:30 by tookuyam          #+#    #+#             */
/*   Updated: 2025/03/08 15:55:03 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"

void	ph_run_die(t_philosopher *philo)
{
	ph_to_status(philo, PH_DOING);
	ph_print_action(philo, PH_DIE);
	ph_msleep_philo((unsigned int)philo->manager->config->time_to_sleep, philo);
}
