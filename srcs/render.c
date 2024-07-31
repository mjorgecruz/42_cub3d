/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:00 by masoares          #+#    #+#             */
/*   Updated: 2024/07/31 10:23:35 by masoares         ###   ########.fr       */
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
	int i;
	
	while (i < cub->img_w)
	{
		double cameraX = 2 * i / cub->img_w - 1; //i is the coordinate in camera space
    	double rayDirX = cub->player->dirX + cub->player->planeX * cameraX;
    	double rayDirY = cub->player->dirY + cub->player->planeY * cameraX;
		int mapX = (int) cub->player->posX; //current square of the map the ray is in
		int mapY = (int) cub->player->posY; //current square of the map the ray is in

		double sideDistX;
    	double sideDistY;

		double deltaDistX; 
      	double deltaDistY;
		
		if (rayDirX != 0)
			deltaDistX = abs(1 / rayDirX);
		else
			deltaDistX = 1e30;
		if (rayDirY != 0)
			deltaDistY = abs(1 / rayDirY);
		else
			deltaDistY = 1e30;
		int stepX;
    	int stepY;

      	double perpWallDist;
		int hit = 0;
		int side;
		
		if (rayDirX < 0)
    	{
    	    stepX = -1;
    	    sideDistX = (cub->player->posX - mapX) * deltaDistX;
    	}
    	else
    	{
    	    stepX = 1;
    	    sideDistX = (mapX + 1.0 - cub->player->posX) * deltaDistX;
    	}
    	if (rayDirY < 0)
    	{
    	    stepY = -1;
    	    sideDistY = (cub->player->posY - mapY) * deltaDistY;
    	}
    	else
    	{
    	    stepY = 1;
    	    sideDistY = (mapY + 1.0 - cub->player->posY) * deltaDistY;
		}
		while (hit == 0)
		{
		
	}
	minimaper(cub);
}
