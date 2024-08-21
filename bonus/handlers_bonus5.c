/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_bonus5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:10:56 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 12:39:58 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	door_col_s_neg_ver(t_data *cub, int door_num);
void	door_col_s_neg_hor(t_data *cub, int door_num);
void	control_door(t_data *cub);
int		control_door_rest(t_data *cub, double ang);
void	help_dor_col_t(t_data *cub);

void	help_dor_col_t(t_data *cub)
{
	cub->player->posx = cub->player->posx + cos(cub->player->p_ang) / 20;
}

void	door_col_s_neg_ver(t_data *cub, int door_num)
{
	if (cub->player->posx > cub->doors[door_num].pos_x)
	{
		if (sin(cub->player->p_ang) / 20 > 0)
			math_helper_door5(cub);
		else
		{
			if (cub->player->posx + sin(cub->player->p_ang) \
				/ 20 > cub->doors[door_num].pos_x + 0.6)
				math_helper_door5(cub);
		}
	}
	else
	{
		if (sin(cub->player->p_ang) / 20 > 0)
		{
			if (cub->player->posx + sin(cub->player->p_ang) \
				/ 20 < cub->doors[door_num].pos_x - 0.6)
				math_helper_door5(cub);
		}
		else
			math_helper_door5(cub);
	}
	math_door4_helper(cub);
}

void	door_col_s_neg_hor(t_data *cub, int door_num)
{
	if (cub->player->posy > cub->doors[door_num].pos_y)
	{
		if (-cos(cub->player->p_ang) / 20 > 0)
			math_door4_helper(cub);
		else
		{
			if (cub->player->posy - cos(cub->player->p_ang) \
				/ 20 > cub->doors[door_num].pos_y + 0.6)
				math_door4_helper(cub);
		}
	}
	else
	{
		if (-cos(cub->player->p_ang) / 20 > 0)
		{
			if (cub->player->posy - cos(cub->player->p_ang) \
				/ 20 < cub->doors[door_num].pos_y - 0.6)
				cub->player->posy = cub->player->posy \
					- cos(cub->player->p_ang) / 20;
		}
		else
			cub->player->posy = cub->player->posy - \
				cos(cub->player->p_ang) / 20;
	}
	math_helper_door5(cub);
}

void	control_door(t_data *cub)
{
	int		door_num;
	double	ang;

	door_num = -1;
	ang = cub->player->p_ang - ((double)(int)(cub->player->p_ang \
		/ (360.0 * DG_RAD))) * (360.0 * DG_RAD);
	if (ang < 0)
		ang += (360.0 * DG_RAD);
	if (cub->doors)
	{
		if ((ang >= (0 * DG_RAD) && ang <= (45 * DG_RAD)) \
			|| (ang < (360 * DG_RAD) && ang >= (315 * DG_RAD)))
		{
			if (cub->map[(int)cub->player->posy][(int)cub->player->posx + 1])
				door_num = search_door(cub, cub->player->posx \
					+ 1, cub->player->posy);
		}
		else
			door_num = control_door_rest(cub, ang);
		if (door_num == -1)
			return ;
		animate_door_opening(cub, door_num);
	}
	return ;
}

int	control_door_rest(t_data *cub, double ang)
{
	int		door_num;

	door_num = -1;
	if (ang > (45 * DG_RAD) && ang <= (135 * DG_RAD))
	{
		if ((int)cub->player->posy + 1 > 0 \
			&& cub->map[(int)cub->player->posy + 1][(int)cub->player->posx])
			door_num = search_door(cub, \
				cub->player->posx, cub->player->posy + 1);
	}
	else if (ang > (135 * DG_RAD) && ang <= (225 * DG_RAD))
	{
		if ((int)cub->player->posx - 1 > 0 \
			&& cub->map[(int)cub->player->posy][(int)cub->player->posx - 1])
			door_num = search_door(cub, \
				cub->player->posx - 1, cub->player->posy);
	}
	else if (ang > (225 * DG_RAD) && ang <= (315 * DG_RAD))
	{
		if ((int)cub->player->posy - 1 < cub->map_h \
			&& cub->map[(int)cub->player->posy - 1][(int)cub->player->posx])
			door_num = search_door(cub, \
				cub->player->posx, cub->player->posy - 1);
	}
	return (door_num);
}
