/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_generate_philosophers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:09:13 by tookuyam          #+#    #+#             */
/*   Updated: 2025/03/08 16:09:08 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph.h"
#include <stdlib.h>
#include <string.h>

static void	ph_init_philosopher(
				t_philosopher *philo, t_manager *manager, int index);

t_philosopher	*ph_generate_philosophers(t_manager *manager)
{
	t_philosopher	*philos;
	int				index;
	int				size;

	size = sizeof(t_philosopher) * manager->config->philo_cnt;
	philos = (t_philosopher *)malloc(size);
	if (philos == NULL)
		return (NULL);
	memset(philos, 0, size);
	index = 0;
	while (index < manager->config->philo_cnt)
	{
		ph_init_philosopher(&philos[index], manager, index);
		index++;
	}
	return (philos);
}

static void	ph_init_philosopher(
				t_philosopher *philo, t_manager *manager, int index)
{
	memset(philo, 0, sizeof(t_philosopher));
	*philo = (t_philosopher){
		.in_process = true,
		.manager = manager,
		.last_eat = manager->start,
		.no = index + 1,
	};
	pthread_mutex_init(&philo->fork, NULL);
	pthread_mutex_init(&philo->lock, NULL);
}
