/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:00 by masoares          #+#    #+#             */
/*   Updated: 2024/08/01 14:23:35 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	run_window(t_data *cub)
{
	
	minimaper_initial(cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, key_detect, cub);
	mlx_hook(cub->win_ptr, DestroyNotify, NoEventMask, close_win_free, cub);
	mlx_loop(cub->mlx_ptr);
}

void render(t_data *cub)
{
	// int i;
	// double cameraX = 2 * i / cub->img_w - 1; //i is the coordinate in camera space
	
	// while (i < cub->img_w)
	// {
    // 	double rayDirX = cub->player->dirX + cub->player->planeX * cameraX;
    // 	double rayDirY = cub->player->dirY + cub->player->planeY * cameraX;
	// 	int mapX = (int) cub->player->posX; //current square of the map the ray is in
	// 	int mapY = (int) cub->player->posY; //current square of the map the ray is in

		double sideDistX; //distance to the next edge in x
    	double sideDistY; //distance to the next edge in y
		double deltaDistX; //distance to progress one unit in x
    	double deltaDistY; //distance to progress one unit in y
		
	// 	if (rayDirX != 0)
	// 		deltaDistX = fabs(1 / rayDirX);
	// 	else
	// 		deltaDistX = 1e30;
	// 	if (rayDirY != 0)
	// 		deltaDistY = fabs(1 / rayDirY);
	// 	else
	// 		deltaDistY = 1e30;
	// 	int stepX;
    // 	int stepY;

    //   	double perpWallDist;
	// 	int hit = 0;
	// 	int side;
		
	// 	if (rayDirX < 0)
    // 	{
    // 	    stepX = -1;
    // 	    sideDistX = (cub->player->posX - mapX) * deltaDistX;
    // 	}
    // 	else
    // 	{
    // 	    stepX = 1;
    // 	    sideDistX = (mapX + 1.0 - cub->player->posX) * deltaDistX;
    // 	}
    // 	if (rayDirY < 0)
    // 	{
    // 	    stepY = -1;
    // 	    sideDistY = (cub->player->posY - mapY) * deltaDistY;
    // 	}
    // 	else
    // 	{
    // 	    stepY = 1;
    // 	    sideDistY = (mapY + 1.0 - cub->player->posY) * deltaDistY;
	// 	}
	// 	while (hit == 0)
	// 	{
    //     	if (sideDistX < sideDistY)
    //     	{
    //     	  sideDistX += deltaDistX;
    //     	  mapX += stepX;
    //     	  side = 0;
    //     	}
    //     	else
    //     	{
    //     	  sideDistY += deltaDistY;
    //     	  mapY += stepY;
    //     	  side = 1;
    //     	}
    //     	//Check if ray has hit a wall
    //     	if (cub->map[mapX][mapY] > 0)
	// 			hit = 1;
    // 	}
	// 	if(side == 0)
	// 		perpWallDist = (sideDistX - deltaDistX);
    // 	else
	// 	    perpWallDist = (sideDistY - deltaDistY);
	// 	int lineHeight = (int)(cub->img_h / perpWallDist);
	// 	int drawStart = -lineHeight / 2 +cub->img_h  / 2;
	// 	if(drawStart < 0)
	// 		drawStart = 0;
	// 	int drawEnd = lineHeight / 2 + cub->img_h  / 2;
	// 	if(drawEnd >= cub->img_h )
	// 		drawEnd = cub->img_h  - 1;
	// 	bresenham_wall(cub,i, i, drawStart, drawEnd);
	// }	
	minimaper(cub);

	
}
