/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:59:22 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 16:59:41 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

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

void	math_helper_door5(t_data *cub)
{
	cub->player->posx = cub->player->posx + sin(cub->player->p_ang) / 20;
}
