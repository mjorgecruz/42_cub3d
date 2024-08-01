/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:26 by masoares          #+#    #+#             */
/*   Updated: 2024/08/01 11:49:14 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	init_fields(t_data *cub)
{
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
	init_map(cub);
	init_orientation(player, cub->player_init_ori);
	init_position(player, cub->map);
	//init_camera(cub);

	return (player);
}

void init_orientation(t_player *player, char player_init_ori)
{
	player->fov = 2 * atan(0.66 / 1);
	if (player_init_ori == 'N')
		player->player_ang = 90 * DG_RAD;
	else if (player_init_ori == 'E')
		player->player_ang = 0 * DG_RAD;
	else if (player_init_ori == 'O')
		player->player_ang = 180 * DG_RAD;
	else
		player->player_ang = -90 * DG_RAD;

	
}

void init_position(t_player *player,int **map)
{
	(void) player;
	(void) map;
	return ;
}

void init_camera(t_data *cub)
{
	t_camera *cam = (t_camera *) malloc(sizeof(t_camera) * 1);
	if (cam == NULL)
		ft_error(CAMERA, cub);
	(cub->player->cam) = cam;
}

void init_map(cub)
{
	
	int ** map;
	int * line;

	
}