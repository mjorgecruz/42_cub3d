/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/08/20 01:24:24 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	key_detect(int key, t_data *cub)
{
	if (key == XK_Escape)
		close_win_free(cub);
	if(key == XK_space)
		control_door(cub);
	if (key == XK_Up || key == XK_w)
		cub->keys.back_front = 1;
	else if (key == XK_Down || key == XK_s)
		cub->keys.back_front = -1;
	else if (key == XK_a)
		cub->keys.left_right = -1;
	else if (key == XK_d)
		cub->keys.left_right = 1;
	else if (key == XK_Left)
		cub->keys.rotate = -1;
	else if (key == XK_Right)
		cub->keys.rotate = 1;
	return (0);
}

int	key_undetect(int key, t_data *cub)
{
	if (key == XK_Escape)
		close_win_free(cub);
	if ((key == XK_Up || key == XK_w) && cub->keys.back_front == 1)
		cub->keys.back_front = 0;
	if ((key == XK_Down || key == XK_s) && cub->keys.back_front == -1)
		cub->keys.back_front = 0;
	if (key == XK_a && cub->keys.left_right == -1)
		cub->keys.left_right = 0;
	if (key == XK_d && cub->keys.left_right == 1)
		cub->keys.left_right = 0;
	if (key == XK_Left && cub->keys.rotate == -1)
		cub->keys.rotate = 0;
	if (key == XK_Right && cub->keys.rotate == 1)
		cub->keys.rotate = 0;
	return (0);
}

void control_rot(t_data *cub, int dir)
{
	cub->player->p_ang += ROT * dir;
	cub->player->pov->dirx = cos(cub->player->p_ang);
	cub->player->pov->diry = sin(cub->player->p_ang);
	if (cub->player->pov->dirx < 0.00001 && cub->player->pov->dirx > -0.00001)
		cub->player->pov->dirx = 0;
	if (cub->player->pov->diry < 0.00001 && cub->player->pov->diry > -0.00001)
		cub->player->pov->diry = 0;	
	cub->player->cam->planex = -cub->player->pov->diry * tan(cub->player->fov / 2);
	cub->player->cam->planey = cub->player->pov->dirx * tan(cub->player->fov / 2);
}

void control_trans(t_data *cub, int dir)
{
	int finalX;
	int finalY;
	int door_num;
	
	if (dir > 0 )
	{
		finalX = (int)(cub->player->posx + cos(cub->player->p_ang)/20);
		finalY = (int)(cub->player->posy + sin(cub->player->p_ang)/20);
		if (cub->map[finalY][(int)(cub->player->posx)] == '0')
			cub->player->posy = cub->player->posy + sin(cub->player->p_ang)/20;
		if (cub->map[(int)(cub->player->posy)][finalX] == '0')
			cub->player->posx = cub->player->posx + cos(cub->player->p_ang)/20;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posx + cos(cub->player->p_ang)/20, cub->player->posy + sin(cub->player->p_ang)/20);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posx + cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_x - 0.2)
						cub->player->posx = cub->player->posx + cos(cub->player->p_ang)/20;
					else if (cub->player->posx + cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_x)
						cub->player->posx = cub->player->posx - 0.2;
					else
						cub->player->posx = cub->player->posx + cos(cub->player->p_ang)/20;
					cub->player->posy = cub->player->posy + sin(cub->player->p_ang)/20;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posy + sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_y - 0.2)
						cub->player->posy = cub->player->posy + sin(cub->player->p_ang)/20;
					else if (cub->player->posy + sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_y)
						cub->player->posy = cub->player->posy - 0.2;
					else
						cub->player->posy = cub->player->posy + sin(cub->player->p_ang)/20;
					cub->player->posx = cub->player->posx + cos(cub->player->p_ang)/20;
				}
			}
			else
			{
				cub->player->posy = cub->player->posy + sin(cub->player->p_ang)/20;
				cub->player->posx = cub->player->posx + cos(cub->player->p_ang)/20;			
			}
		}
	}	
	else
	{
		finalX = (int)(cub->player->posx - cos(cub->player->p_ang)/20);
		finalY = (int)(cub->player->posy - sin(cub->player->p_ang)/20);
		if (cub->map[finalY][(int)(cub->player->posx)] == '0')
			cub->player->posy = cub->player->posy - sin(cub->player->p_ang)/20;
		if (cub->map[(int)(cub->player->posy)][finalX] == '0')
			cub->player->posx = cub->player->posx - cos(cub->player->p_ang)/20;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posx - cos(cub->player->p_ang)/20, cub->player->posy - sin(cub->player->p_ang)/20);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posx - cos(cub->player->p_ang)/20 >= cub->doors[door_num].pos_x + 0.2)
						cub->player->posx = cub->player->posx - cos(cub->player->p_ang)/20;
					else if (cub->player->posx - cos(cub->player->p_ang)/20 >= cub->doors[door_num].pos_x)
						cub->player->posx = cub->player->posx + 0.2;
					else
						cub->player->posx = cub->player->posx - cos(cub->player->p_ang)/20;
					cub->player->posy = cub->player->posy - sin(cub->player->p_ang)/20;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posy - sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_y + 0.2)
						cub->player->posy = cub->player->posy - sin(cub->player->p_ang)/20;
					else if (cub->player->posy - sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_y)
						cub->player->posy = cub->player->posy + 0.2;
					else
						cub->player->posy = cub->player->posy - sin(cub->player->p_ang)/20;
					cub->player->posx = cub->player->posx - cos(cub->player->p_ang)/20;
				}
			}
			else
			{
				cub->player->posy = cub->player->posy - sin(cub->player->p_ang)/20;
				cub->player->posx = cub->player->posx - cos(cub->player->p_ang)/20;			
			}
		}
	}
}

void	control_sides(t_data *cub, int dir)
{
	int finalX;
	int finalY;
	int door_num;
	
	if (dir > 0 )
	{
		finalX = (int)(cub->player->posx - sin(cub->player->p_ang)/20);
		finalY = (int)(cub->player->posy + cos(cub->player->p_ang)/20);
		if (cub->map[finalY][(int)(cub->player->posx)] == '0')
			cub->player->posy = cub->player->posy + cos(cub->player->p_ang)/20;
		if (cub->map[(int)(cub->player->posy)][finalX] == '0')
			cub->player->posx = cub->player->posx -sin(cub->player->p_ang)/20;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posx + cos(cub->player->p_ang)/20, cub->player->posy + sin(cub->player->p_ang)/20);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posx -sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_x - 0.2)
						cub->player->posx = cub->player->posx - sin(cub->player->p_ang)/20;
					else if (cub->player->posx -sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_x)
						cub->player->posx = cub->player->posx - 0.2;
					else
						cub->player->posx = cub->player->posx -sin(cub->player->p_ang)/20;
					cub->player->posy = cub->player->posy + cos(cub->player->p_ang)/20;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posy + cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_y - 0.2)
						cub->player->posy = cub->player->posy + cos(cub->player->p_ang)/20;
					else if (cub->player->posy + cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_y)
						cub->player->posy = cub->player->posy - 0.2;
					else
						cub->player->posy = cub->player->posy + cos(cub->player->p_ang)/20;
					cub->player->posx = cub->player->posx - sin(cub->player->p_ang)/20;
				}
			}
			else
			{
				cub->player->posy = cub->player->posy + cos(cub->player->p_ang)/20;
				cub->player->posx = cub->player->posx + -sin(cub->player->p_ang)/20;			
			}
		}
	}	
	else
	{
		finalX = (int)(cub->player->posx + sin(cub->player->p_ang)/20);
		finalY = (int)(cub->player->posy - cos(cub->player->p_ang)/20);
		if (cub->map[finalY][(int)(cub->player->posx)] == '0')
			cub->player->posy = cub->player->posy - cos(cub->player->p_ang)/20;
		if (cub->map[(int)(cub->player->posy)][finalX] == '0')
			cub->player->posx = cub->player->posx + sin(cub->player->p_ang)/20;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posx + sin(cub->player->p_ang)/20, cub->player->posy - sin(cub->player->p_ang)/20);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posx + sin(cub->player->p_ang)/20 >= cub->doors[door_num].pos_x + 0.2)
						cub->player->posx = cub->player->posx + sin(cub->player->p_ang)/20;
					else if (cub->player->posx + sin(cub->player->p_ang)/20 >= cub->doors[door_num].pos_x)
						cub->player->posx = cub->player->posx + 0.2;
					else
						cub->player->posx = cub->player->posx + sin(cub->player->p_ang)/20;
					cub->player->posy = cub->player->posy - cos(cub->player->p_ang)/20;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posy - cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_y + 0.2)
						cub->player->posy = cub->player->posy - cos(cub->player->p_ang)/20;
					else if (cub->player->posy - cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_y)
						cub->player->posy = cub->player->posy + 0.2;
					else
						cub->player->posy = cub->player->posy - cos(cub->player->p_ang)/20;
					cub->player->posx = cub->player->posx +sin(cub->player->p_ang)/20;
				}
			}
			else
			{
				cub->player->posy = cub->player->posy - cos(cub->player->p_ang)/20;
				cub->player->posx = cub->player->posx + sin(cub->player->p_ang)/20;			
			}
		}
	}
}

void control_door(t_data *cub)
{
	int door_num = -1;
	double ang;

	ang = cub->player->p_ang - ((double)(int)(cub->player->p_ang / (360.0 * DG_RAD)))*(360.0 * DG_RAD);
	if (ang < 0)
		ang += (360.0 * DG_RAD);
	if (cub->doors)
	{
		if (cub->map[(int)cub->player->posy][(int)cub->player->posx] == 'D')
		{
			door_num = search_door(cub, cub->player->posx, cub->player->posy);
		}
  		else if ((ang >= (0 * DG_RAD) &&  ang <= (45 * DG_RAD)) || (ang < (360 * DG_RAD) &&  ang >= (315 * DG_RAD)))
		{
			if (cub->map[(int)cub->player->posy][(int)cub->player->posx + 1])
				door_num = search_door(cub, cub->player->posx + 1, cub->player->posy);
		}
		else if (ang > (45 * DG_RAD) &&  ang <= (135 * DG_RAD))
		{
			if((int)cub->player->posy - 1 > 0 && cub->map[(int)cub->player->posy - 1][(int)cub->player->posx])
				door_num = search_door(cub, cub->player->posx, cub->player->posy - 1);
		}
		else if (ang > (135 * DG_RAD) &&  ang <= (225 * DG_RAD))
		{
			if ((int)cub->player->posx - 1 > 0 && cub->map[(int)cub->player->posy][(int)cub->player->posx - 1])
				door_num = search_door(cub, cub->player->posx - 1, cub->player->posy);
		}
		else if (ang > (225 * DG_RAD) &&  ang <= (315 * DG_RAD))
		{
			if((int)cub->player->posy + 1 < cub->map_h && cub->map[(int)cub->player->posy + 1][(int)cub->player->posx])
				door_num = search_door(cub, cub->player->posx, cub->player->posy + 1);
		}
		if (door_num == -1)
			return;
		animate_door_opening(cub, door_num);
	}
	return;
}

