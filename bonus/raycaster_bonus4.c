/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:59:22 by masoares          #+#    #+#             */
/*   Updated: 2024/08/20 15:45:28 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	distance_doors_within_cam(t_data *cub, int *side, int x)
{
	int	door_num;

	*side = raycaster_recursive(cub, x);
	door_num = search_door(cub, cub->player->posx, cub->player->posy);
	if (cub->doors[door_num].open == true)
		return (0);
	if (cub->doors[door_num].orientation == 1)
		*side = door_side_calc_x(cub);
	else if (cub->doors[door_num].orientation == 0)
		*side = door_side_calc_y(cub);
	return (1);
}
