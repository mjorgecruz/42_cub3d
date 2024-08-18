/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:17:46 by masoares          #+#    #+#             */
/*   Updated: 2024/08/17 22:43:42 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

long	get_time(void)
{
	struct timeval	current;
	double			time;

	gettimeofday(&current, NULL);
	time = current.tv_sec*1000 + current.tv_usec / 1000;
	return (time);
}