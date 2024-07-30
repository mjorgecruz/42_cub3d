/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:26 by masoares          #+#    #+#             */
/*   Updated: 2024/07/30 12:06:40 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_fields(t_data *cub)
{
	init_textures_to_null(cub); //check it
	cub->mlx_ptr = mlx_init();
	if (cub->mlx_ptr == NULL)
		return (-1);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_W, WIN_H, "CUB3D");
	if (cub->win_ptr == NULL)
	{
		free(cub->mlx_ptr);
		free(cub->win_ptr);
		return (-2);
	}
	cub->img_w = 1920;
	cub->img_h = 1080;
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel,
			&cub->line_length, &cub->endian);
	cub->map_h = 0;
	cub->map_w = 0;
	
	cub->map = NULL;
	cub->player = init_player(cub);
	return (0);
}

t_player *init_player(t_data *cub)
{
	t_player *player = (t_player *) malloc(sizeof(t_player) * 1);
	if (player == NULL)
		ft_error(PLAYER, cub);
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
	(void) player;
	(void) map;
	return ;
}

void init_textures_to_null(t_data *cub)
{
	cub->north = NULL;
	cub->south = NULL;
	cub->west = NULL;
	cub->east = NULL;
}