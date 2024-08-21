/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 16:57:55 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int		key_detect(int key, t_data *cub);
int		key_undetect(int key, t_data *cub);
void	control_rot(t_data *cub, int dir);
void	control_trans(t_data *cub, int dir);
void	ctrl_trans_helper(t_data *cub);

int	key_detect(int key, t_data *cub)
{
	if (key == XK_Escape)
		close_win_free(cub);
	if (key == XK_space)
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

void	control_rot(t_data *cub, int dir)
{
	cub->player->p_ang += ROT * dir;
	cub->player->pov->dirx = cos(cub->player->p_ang);
	cub->player->pov->diry = sin(cub->player->p_ang);
	if (cub->player->pov->dirx < 0.00001 && cub->player->pov->dirx > -0.00001)
		cub->player->pov->dirx = 0;
	if (cub->player->pov->diry < 0.00001 && cub->player->pov->diry > -0.00001)
		cub->player->pov->diry = 0;
	cub->player->cam->planex = -cub->player->pov->diry * \
		tan(cub->player->fov / 2);
	cub->player->cam->planey = cub->player->pov->dirx * \
		tan(cub->player->fov / 2);
}

void	control_trans(t_data *cub, int dir)
{
	if (dir > 0)
		control_trans_dirpos(cub);
	else
		control_trans_dirneg(cub);
}

void	ctrl_trans_helper(t_data *cub)
{
	cub->player->posy = cub->player->posy + sin(cub->player->p_ang) / 20;
	cub->player->posx = cub->player->posx + cos(cub->player->p_ang) / 20;
}
