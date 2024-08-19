/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:17:46 by masoares          #+#    #+#             */
/*   Updated: 2024/08/19 16:18:27 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

long	get_time(void);

long	get_time(void)
{
	struct timeval	current;
	double			time;

	gettimeofday(&current, NULL);
	time = current.tv_sec * 1000 + current.tv_usec / 1000;
	return (time);
}
