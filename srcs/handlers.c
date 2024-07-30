/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/07/30 16:34:30 by masoares         ###   ########.fr       */
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
		cub->player->player_ang += DG_RAD;
	else
		(cub->player->player_ang) -= DG_RAD;
}

void control_trans(t_data *cub, int dir)
{
	if (dir > 0)
	{
		cub->player->posX = cub->player->posX + cos(cub->player->player_ang);
		printf("%f\n", cub->player->posX);
		printf("%f\n", cos(cub->player->player_ang));
		
		
		cub->player->posY = cub->player->posY + sin(cub->player->player_ang);
		printf("%f\n", cub->player->posY);
	}	
	else
	{
		cub->player->posX -= (sin(cub->player->player_ang) * 50);
		cub->player->posY -= (cos(cub->player->player_ang) * 50);
	}
}