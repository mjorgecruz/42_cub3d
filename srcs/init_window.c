/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:26 by masoares          #+#    #+#             */
/*   Updated: 2024/07/29 15:35:38 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	init_fields(t_data *cub)
{
	cub->mlx_ptr = mlx_init();
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_W, WIN_H, "CUB3D");
	cub->img_w = 1920;
	cub->img_h = 1080;
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel,
			&cub->line_length, &cub->endian);
	cub->map_h = 0;
	cub->map_w = 0;
	cub->map = NULL;
	cub->player = init_player(cub->player_init_ori);
}

t_player *init_player(t_data *cub)
{
	t_player *player = (t_player *) malloc(sizeof(t_player) * 1);
	if (player == NULL)
		errors(PLAYER, cub);
	init_orientation(player, cub->player_init_ori);
	init_position(player, cub->map);

	return (player);
}

void init_orientation(t_player *player, char player_init_ori)
{
	if (player_init_ori == 'N')
	{	
		player->dirX = 0;
		player->dirY = -1;
	}	
	else if (player_init_ori == 'E')
	{
		player->dirX = 1;
		player->dirY = 0;
		
	}
	else if (player_init_ori == 'O')
	{
		player->dirX = -1;
		player->dirY = 0;
	}
	else
	{
		player->dirX = 0;
		player->dirY = 1;
	}
}

void init_position(t_player *player,int **map)
{
	return ;
}
