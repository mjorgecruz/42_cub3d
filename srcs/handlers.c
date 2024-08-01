/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/08/01 14:25:25 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	key_detect(int key, t_data *cub)
{
	printf("key %x \n", key);
	if (key == XK_Escape)
		close_win_free(cub);
	else if (key == XK_Up)
		control_trans(cub, 1);
	else if (key == XK_Down)
		control_trans(cub, -1);
	else if (key == XK_Left)
		control_rot(cub,-1);
	else if (key == XK_Right)
		control_rot(cub, 1);
	render(cub);
	return (0);
}

void control_rot(t_data *cub, int dir)
{
	if (dir > 0)
		cub->player->player_ang += DG_RAD*5;
	else
		(cub->player->player_ang) -= DG_RAD*5;
}

void control_trans(t_data *cub, int dir)
{
	if (dir > 0)
	{
		cub->player->posX = cub->player->posX + cos(cub->player->player_ang)/10;	
		cub->player->posY = cub->player->posY + sin(cub->player->player_ang)/10;
	}	
	else
	{
		cub->player->posX -= (cos(cub->player->player_ang)/10);
		cub->player->posY -= (sin(cub->player->player_ang)/10);
	}
}