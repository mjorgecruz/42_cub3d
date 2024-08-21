/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_bonus2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 09:47:24 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 16:57:58 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	control_trans_dirpos(t_data *cub);
void	control_trans_dirneg(t_data *cub);
void	tester_pos_trans(t_data *cub, int finalx, int finaly);
void	door_col_t_pos_ver(t_data *cub, int door_num);
void	door_col_t_pos_hor(t_data *cub, int door_num);

void	control_trans_dirpos(t_data *cub)
{
	int	finalx;
	int	finaly;
	int	door_num;

	finalx = (int)(cub->player->posx + cos(cub->player->p_ang) / 20);
	finaly = (int)(cub->player->posy + sin(cub->player->p_ang) / 20);
	tester_pos_trans(cub, finalx, finaly);
	if (cub->map[finaly][finalx] == 'D')
	{
		door_num = search_door(cub, cub->player->posx + \
			cos(cub->player->p_ang) / 20, cub->player->posy + \
			sin(cub->player->p_ang) / 20);
		if (cub->doors[door_num].open == false)
		{
			if (cub->doors[door_num].orientation == 1)
				door_col_t_pos_ver(cub, door_num);
			else if (cub->doors[door_num].orientation == 0)
				door_col_t_pos_hor(cub, door_num);
		}
		else
			ctrl_trans_helper(cub);
	}
}

void	control_trans_dirneg(t_data *cub)
{
	int	finalx;
	int	finaly;
	int	door_num;

	finalx = (int)(cub->player->posx - cos(cub->player->p_ang) / 20);
	finaly = (int)(cub->player->posy - sin(cub->player->p_ang) / 20);
	tester_neg_trans(cub, finalx, finaly);
	if (cub->map[finaly][finalx] == 'D')
	{
		door_num = search_door(cub, cub->player->posx - \
			cos(cub->player->p_ang) / 20, cub->player->posy - \
				sin(cub->player->p_ang) / 20);
		if (cub->doors[door_num].open == false)
		{
			if (cub->doors[door_num].orientation == 1)
				door_col_t_neg_ver(cub, door_num);
			else if (cub->doors[door_num].orientation == 0)
				door_col_t_neg_hor(cub, door_num);
		}
		else
			ctrl_trans_helper_neg(cub);
	}
}

void	tester_pos_trans(t_data *cub, int finalx, int finaly)
{
	if (cub->map[finaly][(int)(cub->player->posx)] == '0')
		cub->player->posy = cub->player->posy + \
			sin(cub->player->p_ang) / 20;
	if (cub->map[(int)(cub->player->posy)][finalx] == '0')
		cub->player->posx = cub->player->posx + \
			cos(cub->player->p_ang) / 20;
}

void	door_col_t_pos_ver(t_data *cub, int door_num)
{
	if (cub->player->posx > cub->doors[door_num].pos_x)
	{
		if (cos(cub->player->p_ang) / 20 > 0)
			help_dor_col_t(cub);
		else
		{
			if (cub->player->posx + cos(cub->player->p_ang) / 20 > \
				cub->doors[door_num].pos_x + 0.6)
				help_dor_col_t(cub);
		}
	}
	else
	{
		if (cos(cub->player->p_ang) / 20 > 0)
		{
			if (cub->player->posx + cos(cub->player->p_ang) / 20 \
				< cub->doors[door_num].pos_x - 0.6)
				help_dor_col_t(cub);
		}
		else
			help_dor_col_t(cub);
	}
	cub->player->posy = cub->player->posy + sin(cub->player->p_ang) / 20;
}

void	door_col_t_pos_hor(t_data *cub, int door_num)
{
	if (cub->player->posy > cub->doors[door_num].pos_y)
	{
		if (sin(cub->player->p_ang) / 20 > 0)
			door_pos_hor_helper(cub);
		else
		{
			if (cub->player->posy + sin(cub->player->p_ang) / 20 \
				> cub->doors[door_num].pos_y + 0.6)
				door_pos_hor_helper(cub);
		}
	}
	else
	{
		if (sin(cub->player->p_ang) / 20 > 0)
		{
			if (cub->player->posy + sin(cub->player->p_ang) / 20 \
				< cub->doors[door_num].pos_y - 0.6)
				door_pos_hor_helper(cub);
		}
		else
			door_pos_hor_helper(cub);
	}
	cub->player->posx = cub->player->posx + cos(cub->player->p_ang) / 20;
}
