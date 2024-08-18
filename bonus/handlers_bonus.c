/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/08/18 02:43:43 by masoares         ###   ########.fr       */
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
	cub->player->pov->dirX = cos(cub->player->p_ang);
	cub->player->pov->dirY = sin(cub->player->p_ang);
	if (cub->player->pov->dirX < 0.00001 && cub->player->pov->dirX > -0.00001)
		cub->player->pov->dirX = 0;
	if (cub->player->pov->dirY < 0.00001 && cub->player->pov->dirY > -0.00001)
		cub->player->pov->dirY = 0;	
	cub->player->cam->planeX = -cub->player->pov->dirY * tan(cub->player->fov / 2);
	cub->player->cam->planeY = cub->player->pov->dirX * tan(cub->player->fov / 2);
}

void control_trans(t_data *cub, int dir)
{
	int finalX;
	int finalY;
	int door_num;
	
	if (dir > 0 )
	{
		finalX = (int)(cub->player->posX + cos(cub->player->p_ang)/20);
		finalY = (int)(cub->player->posY + sin(cub->player->p_ang)/20);
		if (cub->map[finalY][(int)(cub->player->posX)] == '0')
			cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/20;
		if (cub->map[(int)(cub->player->posY)][finalX] == '0')
			cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/20;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posX + cos(cub->player->p_ang)/20, cub->player->posY + sin(cub->player->p_ang)/20);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posX + cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_x - 0.2)
						cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/20;
					else if (cub->player->posX + cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_x)
						cub->player->posX = cub->player->posX - 0.2;
					else
						cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/20;
					cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/20;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posY + sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_y - 0.2)
						cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/20;
					else if (cub->player->posY + sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_y)
						cub->player->posY = cub->player->posY - 0.2;
					else
						cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/20;
					cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/20;
				}
			}
			else
			{
				cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/20;
				cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/20;			
			}
		}
	}	
	else
	{
		finalX = (int)(cub->player->posX - cos(cub->player->p_ang)/20);
		finalY = (int)(cub->player->posY - sin(cub->player->p_ang)/20);
		if (cub->map[finalY][(int)(cub->player->posX)] == '0')
			cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/20;
		if (cub->map[(int)(cub->player->posY)][finalX] == '0')
			cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/20;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posX - cos(cub->player->p_ang)/20, cub->player->posY - sin(cub->player->p_ang)/20);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posX - cos(cub->player->p_ang)/20 >= cub->doors[door_num].pos_x + 0.2)
						cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/20;
					else if (cub->player->posX - cos(cub->player->p_ang)/20 >= cub->doors[door_num].pos_x)
						cub->player->posX = cub->player->posX + 0.2;
					else
						cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/20;
					cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/20;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posY - sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_y + 0.2)
						cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/20;
					else if (cub->player->posY - sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_y)
						cub->player->posY = cub->player->posY + 0.2;
					else
						cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/20;
					cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/20;
				}
			}
			else
			{
				cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/20;
				cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/20;			
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
		finalX = (int)(cub->player->posX - sin(cub->player->p_ang)/20);
		finalY = (int)(cub->player->posY + cos(cub->player->p_ang)/20);
		if (cub->map[finalY][(int)(cub->player->posX)] == '0')
			cub->player->posY = cub->player->posY + cos(cub->player->p_ang)/20;
		if (cub->map[(int)(cub->player->posY)][finalX] == '0')
			cub->player->posX = cub->player->posX -sin(cub->player->p_ang)/20;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posX + cos(cub->player->p_ang)/20, cub->player->posY + sin(cub->player->p_ang)/20);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posX -sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_x - 0.2)
						cub->player->posX = cub->player->posX - sin(cub->player->p_ang)/20;
					else if (cub->player->posX -sin(cub->player->p_ang)/20 < cub->doors[door_num].pos_x)
						cub->player->posX = cub->player->posX - 0.2;
					else
						cub->player->posX = cub->player->posX -sin(cub->player->p_ang)/20;
					cub->player->posY = cub->player->posY + cos(cub->player->p_ang)/20;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posY + cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_y - 0.2)
						cub->player->posY = cub->player->posY + cos(cub->player->p_ang)/20;
					else if (cub->player->posY + cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_y)
						cub->player->posY = cub->player->posY - 0.2;
					else
						cub->player->posY = cub->player->posY + cos(cub->player->p_ang)/20;
					cub->player->posX = cub->player->posX - sin(cub->player->p_ang)/20;
				}
			}
			else
			{
				cub->player->posY = cub->player->posY + cos(cub->player->p_ang)/20;
				cub->player->posX = cub->player->posX + -sin(cub->player->p_ang)/20;			
			}
		}
	}	
	else
	{
		finalX = (int)(cub->player->posX + sin(cub->player->p_ang)/20);
		finalY = (int)(cub->player->posY - cos(cub->player->p_ang)/20);
		if (cub->map[finalY][(int)(cub->player->posX)] == '0')
			cub->player->posY = cub->player->posY - cos(cub->player->p_ang)/20;
		if (cub->map[(int)(cub->player->posY)][finalX] == '0')
			cub->player->posX = cub->player->posX + sin(cub->player->p_ang)/20;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posX + sin(cub->player->p_ang)/20, cub->player->posY - sin(cub->player->p_ang)/20);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posX + sin(cub->player->p_ang)/20 >= cub->doors[door_num].pos_x + 0.2)
						cub->player->posX = cub->player->posX + sin(cub->player->p_ang)/20;
					else if (cub->player->posX + sin(cub->player->p_ang)/20 >= cub->doors[door_num].pos_x)
						cub->player->posX = cub->player->posX + 0.2;
					else
						cub->player->posX = cub->player->posX + sin(cub->player->p_ang)/20;
					cub->player->posY = cub->player->posY - cos(cub->player->p_ang)/20;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posY - cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_y + 0.2)
						cub->player->posY = cub->player->posY - cos(cub->player->p_ang)/20;
					else if (cub->player->posY - cos(cub->player->p_ang)/20 < cub->doors[door_num].pos_y)
						cub->player->posY = cub->player->posY + 0.2;
					else
						cub->player->posY = cub->player->posY - cos(cub->player->p_ang)/20;
					cub->player->posX = cub->player->posX +sin(cub->player->p_ang)/20;
				}
			}
			else
			{
				cub->player->posY = cub->player->posY - cos(cub->player->p_ang)/20;
				cub->player->posX = cub->player->posX + sin(cub->player->p_ang)/20;			
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
		if (cub->map[(int)cub->player->posY][(int)cub->player->posX] == 'D')
		{
			door_num = search_door(cub, cub->player->posX, cub->player->posY);
		}
  		else if ((ang >= (0 * DG_RAD) &&  ang <= (45 * DG_RAD)) || (ang < (360 * DG_RAD) &&  ang >= (315 * DG_RAD)))
		{
			if (cub->map[(int)cub->player->posY][(int)cub->player->posX + 1])
				door_num = search_door(cub, cub->player->posX + 1, cub->player->posY);
		}
		else if (ang > (45 * DG_RAD) &&  ang <= (135 * DG_RAD))
		{
			if((int)cub->player->posY - 1 > 0 && cub->map[(int)cub->player->posY - 1][(int)cub->player->posX])
				door_num = search_door(cub, cub->player->posX, cub->player->posY - 1);
		}
		else if (ang > (135 * DG_RAD) &&  ang <= (225 * DG_RAD))
		{
			if ((int)cub->player->posX - 1 > 0 && cub->map[(int)cub->player->posY][(int)cub->player->posX - 1])
				door_num = search_door(cub, cub->player->posX - 1, cub->player->posY);
		}
		else if (ang > (225 * DG_RAD) &&  ang <= (315 * DG_RAD))
		{
			if((int)cub->player->posY + 1 < cub->map_h && cub->map[(int)cub->player->posY + 1][(int)cub->player->posX])
				door_num = search_door(cub, cub->player->posX, cub->player->posY + 1);
		}
		if (door_num == -1)
			return;
		animate_door_opening(cub, door_num);
	}
	return;
}

