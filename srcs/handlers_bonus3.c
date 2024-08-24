/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_bonus3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:51:50 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/24 16:34:22 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	tester_neg_trans(t_data *cub, int finalx, int finaly);
void	door_col_t_neg_ver(t_data *cub, int door_num);
void	door_col_t_neg_hor(t_data *cub, int door_num);
void	control_sides(t_data *cub, int dir);
void	control_sides_dirpos(t_data *cub);

void	tester_neg_trans(t_data *cub, int finalx, int finaly)
{
	if (cub->map[finaly][(int)(cub->player->posx)] == '0')
		door_math_helper(cub);
	if (cub->map[(int)(cub->player->posy)][finalx] == '0')
		cub->player->posx = cub->player->posx - cos(cub->player->p_ang) / 20;
}

void	door_col_t_neg_ver(t_data *cub, int door_num)
{
	if (cub->player->posx > cub->doors[door_num].pos_x)
	{
		if (-cos(cub->player->p_ang) / 20 > 0)
			door_neg_ver_helper(cub);
		else
		{
			if (cub->player->posx - cos(cub->player->p_ang) / 20 \
				> cub->doors[door_num].pos_x + 0.6)
				door_neg_ver_helper(cub);
		}
	}
	else
	{
		if (-cos(cub->player->p_ang) / 20 > 0)
		{
			if (cub->player->posx - cos(cub->player->p_ang) / \
				20 < cub->doors[door_num].pos_x - 0.6)
				door_neg_ver_helper(cub);
		}
		else
			door_neg_ver_helper(cub);
	}
	door_math_helper(cub);
}

void	door_col_t_neg_hor(t_data *cub, int door_num)
{
	if (cub->player->posy > cub->doors[door_num].pos_y)
	{
		if (-sin(cub->player->p_ang) / 20 > 0)
			door_math_helper(cub);
		else
		{
			if (cub->player->posy - sin(cub->player->p_ang) / 20 \
				> cub->doors[door_num].pos_y + 0.6)
				door_math_helper(cub);
		}
	}
	else
	{
		if (-sin(cub->player->p_ang) / 20 > 0)
		{
			if (cub->player->posy - sin(cub->player->p_ang) / 20 \
				< cub->doors[door_num].pos_y - 0.6)
				door_math_helper(cub);
		}
		else
			door_math_helper(cub);
	}
	door_neg_ver_helper(cub);
}

void	control_sides(t_data *cub, int dir)
{
	if (dir > 0)
		control_sides_dirpos(cub);
	else
		control_sides_dirneg(cub);
}

void	control_sides_dirpos(t_data *cub)
{
	int	finalx;
	int	finaly;
	int	door_num;

	finalx = (int)(cub->player->posx - sin(cub->player->p_ang) / 20);
	finaly = (int)(cub->player->posy + cos(cub->player->p_ang) / 20);
	tester_side_pos(cub, finalx, finaly);
	if (cub->map[finaly][finalx] == 'D')
	{
		door_num = search_door(cub, cub->player->posx - \
		sin(cub->player->p_ang) / 20, cub->player->posy + \
			cos(cub->player->p_ang) / 20);
		if (cub->doors[door_num].open == false)
		{
			if (cub->doors[door_num].orientation == 1)
				door_col_s_pos_ver(cub, door_num);
			else if (cub->doors[door_num].orientation == 0)
				door_col_s_pos_hor(cub, door_num);
		}
		else
			ctrl_sid_dirposhelper(cub);
	}
}
