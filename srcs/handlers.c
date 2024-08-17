/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/08/17 10:46:32 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_detect(int key, t_data *cub);
void	control_rot(t_data *cub, int dir);
void	control_trans(t_data *cub, int dir);

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
	cub->player->pov->dirx = cos(cub->player->p_ang);
	cub->player->pov->diry = sin(cub->player->p_ang);
	if (cub->player->pov->dirx < 0.00001 && cub->player->pov->dirx > -0.00001)
		cub->player->pov->dirx = 0;
	if (cub->player->pov->diry < 0.00001 && cub->player->pov->diry > -0.00001)
		cub->player->pov->diry = 0;
	cub->player->cam->planex = (-cub->player->pov->diry) * \
		tan(cub->player->fov / 2);
	cub->player->cam->planey = cub->player->pov->dirx * \
		tan(cub->player->fov / 2);
}

void	control_trans(t_data *cub, int dir)
{
	int	finalx;
	int	finaly;

	if (dir > 0)
	{
		finalx = (int)(cub->player->posx + cos(cub->player->p_ang) / 10);
		finaly = (int)(cub->player->posy + \
			sin(cub->player->p_ang) / 10);
		if (cub->map[finaly][(int)(cub->player->posx)] == '0')
			cub->player->posy = cub->player->posy + \
				sin(cub->player->p_ang) / 10;
		if (cub->map[(int)(cub->player->posy)][finalx] == '0')
			cub->player->posx = cub->player->posx + \
				cos(cub->player->p_ang) / 10;
	}
	else
	{
		finalx = (int)(cub->player->posx - cos(cub->player->p_ang) / 10);
		finaly = (int)(cub->player->posy - sin(cub->player->p_ang) / 10);
		if (cub->map[(int)(cub->player->posy)][finalx] == '0')
			cub->player->posx -= (cos(cub->player->p_ang) / 10);
		if (cub->map[finaly][(int)(cub->player->posx)] == '0')
			cub->player->posy -= (sin(cub->player->p_ang) / 10);
	}
}
