/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tookuyam <tookuyam@student.42tokyo.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:56:51 by tookuyam          #+#    #+#             */
/*   Updated: 2024/08/11 20:56:51 by tookuyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ph_print_error(const char *str)
{
	int		size;
	ssize_t	len;

	size = 0;
	while (str[size] != '\0')
		size++;
	len = write(2, str, size);
	if (len == -1)
		return ;
	return ;
}
