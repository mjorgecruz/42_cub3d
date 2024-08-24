/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper_extra_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:07:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/24 16:35:04 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	hit_point_vertical_door(t_data *cub);
void	hit_point_horizontal_door(t_data *cub);

void	hit_point_vertical_door(t_data *cub)
{
	cub->player->pov->hitx = (double) cub->player->pov->mapx + 0.5;
	cub->player->pov->hity = cub->player->posy + \
		(cub->player->pov->sidedistx) * cub->player->pov->diry;
}

void	hit_point_horizontal_door(t_data *cub)
{
	cub->player->pov->hitx = cub->player->posx + \
		(cub->player->pov->sidedisty) * cub->player->pov->dirx;
	cub->player->pov->hity = cub->player->pov->mapy + 0.5;
}
