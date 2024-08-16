/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/08/16 16:06:03 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

int	key_detect(int key, t_data *cub)
{
	if (key == XK_Escape)
		close_win_free(cub);
	else if(key == XK_space)
		control_door(cub);
	else if (key == XK_Up || key == XK_w)
		control_trans(cub, 1);
	else if (key == XK_Down || key == XK_s)
		control_trans(cub, -1);
	else if (key == XK_Left || key == XK_a)
		control_rot(cub,-1);
	else if (key == XK_Right || key == XK_d)
		control_rot(cub, 1);
	render_bonus(cub);
	return (0);
}

void control_rot(t_data *cub, int dir)
{
	if (dir > 0)
		cub->player->p_ang += DG_RAD*5;
	else
		(cub->player->p_ang) -= DG_RAD*5;
		
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
		finalX = (int)(cub->player->posX + cos(cub->player->p_ang)/10);
		finalY = (int)(cub->player->posY + sin(cub->player->p_ang)/10);
		if (cub->map[finalY][(int)(cub->player->posX)] == '0')
			cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/10;
		if (cub->map[(int)(cub->player->posY)][finalX] == '0')
			cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/10;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posX + cos(cub->player->p_ang)/10, cub->player->posY + sin(cub->player->p_ang)/10);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posX + cos(cub->player->p_ang)/10 < cub->doors[door_num].pos_x - 0.2)
						cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/10;
					else if (cub->player->posX + cos(cub->player->p_ang)/10 < cub->doors[door_num].pos_x)
						cub->player->posX = cub->player->posX - 0.2;
					else
						cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/10;
					cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/10;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posY + sin(cub->player->p_ang)/10 < cub->doors[door_num].pos_y - 0.2)
						cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/10;
					else if (cub->player->posY + sin(cub->player->p_ang)/10 < cub->doors[door_num].pos_y)
						cub->player->posY = cub->player->posY - 0.2;
					else
						cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/10;
					cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/10;
				}
			}
			else
			{
				cub->player->posY = cub->player->posY + sin(cub->player->p_ang)/10;
				cub->player->posX = cub->player->posX + cos(cub->player->p_ang)/10;			
			}
		}
	}	
	else
	{
		finalX = (int)(cub->player->posX - cos(cub->player->p_ang)/10);
		finalY = (int)(cub->player->posY - sin(cub->player->p_ang)/10);
		if (cub->map[finalY][(int)(cub->player->posX)] == '0')
			cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/10;
		if (cub->map[(int)(cub->player->posY)][finalX] == '0')
			cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/10;
		if (cub->map[finalY][finalX] == 'D')
		{
			door_num = search_door(cub, cub->player->posX - cos(cub->player->p_ang)/10, cub->player->posY - sin(cub->player->p_ang)/10);
			if (cub->doors[door_num].open == false)
			{
				if (cub->doors[door_num].orientation == 1)
				{
					if (cub->player->posX - cos(cub->player->p_ang)/10 >= cub->doors[door_num].pos_x + 0.2)
						cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/10;
					else if (cub->player->posX - cos(cub->player->p_ang)/10 >= cub->doors[door_num].pos_x)
						cub->player->posX = cub->player->posX + 0.2;
					else
						cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/10;
					cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/10;
				}
				else if (cub->doors[door_num].orientation == 0)
				{
					if (cub->player->posY - sin(cub->player->p_ang)/10 < cub->doors[door_num].pos_y + 0.2)
						cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/10;
					else if (cub->player->posY - sin(cub->player->p_ang)/10 < cub->doors[door_num].pos_y)
						cub->player->posY = cub->player->posY + 0.2;
					else
						cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/10;
					cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/10;
				}
			}
			else
			{
				cub->player->posY = cub->player->posY - sin(cub->player->p_ang)/10;
				cub->player->posX = cub->player->posX - cos(cub->player->p_ang)/10;			
			}
		}
	}
}
void control_door(t_data *cub)
{
	int door_num;
	
	if (cub->doors)
	{
		door_num = search_door(cub, cub->player->posX, cub->player->posY);
		if (door_num == -1)
			return;
		cub->doors[door_num].open = !cub->doors[door_num].open;
	}
	return;
}