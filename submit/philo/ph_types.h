/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:40:42 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 19:40:42 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_TYPES_H
# define PH_TYPES_H

# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_action_queue		t_action_queue;
typedef struct s_philosopher		t_philosopher;
typedef struct s_ph_manager			t_manager;
typedef enum e_philo_action			t_philo_action;
typedef enum e_philo_status			t_philo_status;
typedef struct s_log_info			t_log_info;
typedef struct s_ph_config			t_ph_config;

enum e_philo_status
{
	PH_NONE,
	PH_DOING,
	PH_DONE,
	PH_HAS_ORDER,
};

enum e_philo_action
{
	PH_ACT_NONE,
	PH_EAT,
	PH_PICK_UP,
	PH_SLEEP,
	PH_THINK,
	PH_DIE,
};

struct s_ph_config
{
	struct timeval	die_tv;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	int				philo_cnt;
};

struct	s_ph_manager
{
	struct timeval	start;
	int				target_no;
	t_ph_config		*config;
	t_action_queue	*action_queue;
	t_philosopher	*philos;
	bool			in_process;
	pthread_mutex_t	lock;
};

struct s_philosopher
{
	int				no;
	int				eat_cnt;
	pthread_mutex_t	fork;
	struct timeval	last_eat;
	bool			is_eating;
	bool			eating_order;
	bool			in_process;
	t_philo_status	status;
	t_philo_action	ordered_action;
	pthread_mutex_t	lock;
	t_manager		*manager;
};

struct s_log_info
{
	int				no;
	struct timeval	tv;
	t_philo_action	action;
};

struct s_action_queue
{
	t_log_info		*infos;
	int				top;
	int				bottom;
	int				size;
	int				max_size;
	pthread_mutex_t	lock;
};

#endif
