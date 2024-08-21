/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:33 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 16:57:05 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

long	get_time(void);

long	get_time(void)
{
	struct timeval	current;
	double			time;

	gettimeofday(&current, NULL);
	time = current.tv_sec * 1000 + current.tv_usec / 1000;
	return (time);
}
