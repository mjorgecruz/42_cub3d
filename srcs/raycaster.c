/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:30:25 by masoares          #+#    #+#             */
/*   Updated: 2024/08/10 03:04:41 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void display(t_data *cub)
{
	int x;
	
	x = 0;
	
	direction_calc(cub, 0);
	while(x < WIN_W)
	{
		cub->player->cam->cameraX = 2 * x / WIN_H - 1; 
		cub->player->cam->rayDirX = cub->player->pov->dirX + cub->player->cam->planeX * cub->player->cam->cameraX;
		cub->player->cam->rayDirY = cub->player->pov->dirY + cub->player->cam->planeY * cub->player->cam->cameraX;
		x++;
	}
	
}