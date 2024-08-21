/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimaper_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:29:11 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 14:07:25 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	side_calc_helper(t_data *cub);
int	side_calc_helper_2(t_data *cub);
int	side_calc(t_data *cub);
int	search_door(t_data *cub, double x, double y);
int	search_fire(t_data *cub, double x, double y);

int	side_calc_helper(t_data *cub)
{
	cub->player->pov->sidedistx += cub->player->pov->deltax;
	cub->player->pov->mapx += cub->player->pov->stepx;
	return (1);
}

int	side_calc_helper_2(t_data *cub)
{
	cub->player->pov->sidedisty += cub->player->pov->deltay;
	cub->player->pov->mapy += cub->player->pov->stepy;
	return (0);
}

int	side_calc(t_data *cub)
{
	int	hit;
	int	side;

	side = 0;
	hit = 0;
	if (cub->map[(int)cub->player->posy][(int)cub->player->posx] == 'D')
		hit = distance_doors_within(cub, &side);
	while (hit == 0)
	{
		if (fabs(cub->player->pov->sidedistx) < \
			fabs(cub->player->pov->sidedisty))
			side = side_calc_helper(cub);
		else
			side = side_calc_helper_2(cub);
		if (cub->map[cub->player->pov->mapy][cub->player->pov->mapx] > '0')
			hit = distance_doors(cub, &side);
	}
	return (side);
}

int	search_door(t_data *cub, double x, double y)
{
	int	i;

	i = 0;
	if (cub->doors)
	{
		while (cub->doors[i].orientation != -1)
		{
			if ((int)cub->doors[i].pos_x == (int) x)
			{
				if ((int)cub->doors[i].pos_y == (int) y)
					return (i);
			}
			i++;
		}
	}
	return (-1);
}

int	search_fire(t_data *cub, double x, double y)
{
	int	i;

	i = 0;
	while (cub->fires[i].pos_x != -1)
	{
		if ((int)cub->fires[i].pos_x == (int) x)
		{
			if ((int)cub->fires[i].pos_y == (int) y)
				return (i);
		}
		i++;
	}
	return (-1);
}
