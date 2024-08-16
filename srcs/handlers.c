/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/08/16 17:59:31 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_detect(int key, t_data *cub)
{
	if (key == XK_Escape)
		close_win_free(cub);
	else if (key == XK_Up)
		control_trans(cub, 1);
	else if (key == XK_Down)
		control_trans(cub, -1);
	else if (key == XK_Left)
		control_rot(cub, -1);
	else if (key == XK_Right)
		control_rot(cub, 1);
	render(cub);
	return (0);
}

void	control_rot(t_data *cub, int dir)
{
	if (dir > 0)
		cub->player->p_ang += DG_RAD * 5;
	else
		(cub->player->p_ang) -= DG_RAD * 5;
	cub->player->pov->dirX = cos(cub->player->p_ang);
	cub->player->pov->dirY = sin(cub->player->p_ang);
	if (cub->player->pov->dirX < 0.00001 && cub->player->pov->dirX > -0.00001)
		cub->player->pov->dirX = 0;
	if (cub->player->pov->dirY < 0.00001 && cub->player->pov->dirY > -0.00001)
		cub->player->pov->dirY = 0;
	cub->player->cam->planeX = (-cub->player->pov->dirY) * \
		tan(cub->player->fov / 2);
	cub->player->cam->planeY = cub->player->pov->dirX * \
		tan(cub->player->fov / 2);
}

void	control_trans(t_data *cub, int dir)
{
	int	finalx;
	int	finaly;

	if (dir > 0)
	{
		finalx = (int)(cub->player->posX + cos(cub->player->p_ang) / 10);
		finaly = (int)(cub->player->posY + \
			sin(cub->player->p_ang) / 10);
		if (cub->map[finaly][(int)(cub->player->posX)] == '0')
			cub->player->posY = cub->player->posY + \
				sin(cub->player->p_ang) / 10;
		if (cub->map[(int)(cub->player->posY)][finalx] == '0')
			cub->player->posX = cub->player->posX + \
				cos(cub->player->p_ang) / 10;
	}
	else
	{
		finalx = (int)(cub->player->posX - cos(cub->player->p_ang) / 10);
		finaly = (int)(cub->player->posY - sin(cub->player->p_ang) / 10);
		if (cub->map[(int)(cub->player->posY)][finalx] == '0')
			cub->player->posX -= (cos(cub->player->p_ang) / 10);
		if (cub->map[finaly][(int)(cub->player->posX)] == '0')
			cub->player->posY -= (sin(cub->player->p_ang) / 10);
	}
}
