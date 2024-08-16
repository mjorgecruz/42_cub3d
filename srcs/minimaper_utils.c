/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:02:30 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/16 17:05:54 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	direction_calc(t_data *cub, double ang)
{
	cub->player->pov->dirX = cos(cub->player->p_ang + ang);
	cub->player->pov->dirY = sin(cub->player->p_ang + ang);
	if (cub->player->pov->dirX < 0.00001 && cub->player->pov->dirX > -0.00001)
		cub->player->pov->dirX = 0;
	if (cub->player->pov->dirY < 0.00001 && cub->player->pov->dirY > -0.00001)
		cub->player->pov->dirY = 0;
}

void	delta_calc(t_data *cub)
{
	cub->player->pov->mapX = (int)cub->player->posX;
	cub->player->pov->mapY = (int)cub->player->posY;
	if (cub->player->pov->dirX != 0)
		cub->player->pov->deltaX = fabs(1 / cub->player->pov->dirX);
	else
		cub->player->pov->deltaX = 1e30;
	if (cub->player->pov->dirY != 0)
		cub->player->pov->deltaY = fabs(1 / cub->player->pov->dirY);
	else
		cub->player->pov->deltaY = 1e30;
}

void	step_calc(t_data *cub)
{
	if (cub->player->pov->dirX < 0)
	{
		cub->player->pov->stepX = -1;
		cub->player->pov->sideDistX = (cub->player->posX - \
				cub->player->pov->mapX) * cub->player->pov->deltaX;
	}
	else
	{
		cub->player->pov->stepX = 1;
		cub->player->pov->sideDistX = (cub->player->pov->mapX + 1.0 - \
				cub->player->posX) * cub->player->pov->deltaX;
	}
	if (cub->player->pov->dirY < 0)
	{
		cub->player->pov->stepY = -1;
		cub->player->pov->sideDistY = (cub->player->posY - \
				cub->player->pov->mapY) * cub->player->pov->deltaY;
	}
	else
	{
		cub->player->pov->stepY = 1;
		cub->player->pov->sideDistY = (cub->player->pov->mapY + \
				1.0 - cub->player->posY) * cub->player->pov->deltaY;
	}
}

int	side_calc(t_data *cub)
{
	int	hit;
	int	side;

	side = 0;
	hit = 0;
	while (hit == 0)
	{
		if (fabs(cub->player->pov->sideDistX) < \
				fabs(cub->player->pov->sideDistY))
		{
			cub->player->pov->sideDistX += cub->player->pov->deltaX;
			cub->player->pov->mapX += cub->player->pov->stepX;
			side = 1;
		}
		else
		{
			cub->player->pov->sideDistY += cub->player->pov->deltaY;
			cub->player->pov->mapY += cub->player->pov->stepY;
			side = 0;
		}
		if (cub->map[cub->player->pov->mapY][cub->player->pov->mapX] > '0')
			hit = 1;
	}
	return (side);
}
