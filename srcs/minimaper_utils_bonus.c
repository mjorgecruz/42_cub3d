/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:16:41 by masoares          #+#    #+#             */
/*   Updated: 2024/08/24 16:36:04 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	direction_calc(t_data *cub, double ang);
void	delta_calc(t_data *cub);
void	step_calc(t_data *cub);

void	direction_calc(t_data *cub, double ang)
{
	cub->player->pov->dirx = cos(cub->player->p_ang + ang);
	cub->player->pov->diry = sin(cub->player->p_ang + ang);
	if (cub->player->pov->dirx < 0.00001 && cub->player->pov->dirx > -0.00001)
		cub->player->pov->dirx = 0;
	if (cub->player->pov->diry < 0.00001 && cub->player->pov->diry > -0.00001)
		cub->player->pov->diry = 0;
}

void	delta_calc(t_data *cub)
{
	cub->player->pov->mapx = (int)cub->player->posx;
	cub->player->pov->mapy = (int)cub->player->posy;
	if (cub->player->pov->dirx != 0)
		cub->player->pov->deltax = fabs(1 / cub->player->pov->dirx);
	else
		cub->player->pov->deltax = 1e30;
	if (cub->player->pov->diry != 0)
		cub->player->pov->deltay = fabs(1 / cub->player->pov->diry);
	else
		cub->player->pov->deltay = 1e30;
}

void	step_calc(t_data *cub)
{
	if (cub->player->pov->dirx < 0)
	{
		cub->player->pov->stepx = -1;
		cub->player->pov->sidedistx = (cub->player->posx - \
			cub->player->pov->mapx) * cub->player->pov->deltax;
	}
	else
	{
		cub->player->pov->stepx = 1;
		cub->player->pov->sidedistx = (cub->player->pov->mapx + 1.0 - \
			cub->player->posx) * cub->player->pov->deltax;
	}
	if (cub->player->pov->diry < 0)
	{
		cub->player->pov->stepy = -1;
		cub->player->pov->sidedisty = (cub->player->posy - \
			cub->player->pov->mapy) * cub->player->pov->deltay;
	}
	else
	{
		cub->player->pov->stepy = 1;
		cub->player->pov->sidedisty = (cub->player->pov->mapy + 1.0 - \
			cub->player->posy) * cub->player->pov->deltay;
	}
}
