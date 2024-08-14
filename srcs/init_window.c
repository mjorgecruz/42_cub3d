/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:26 by masoares          #+#    #+#             */
/*   Updated: 2024/08/14 15:51:21 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	init_fields(t_data *cub)
{
	cub->mlx_ptr = mlx_init();
	if (cub->mlx_ptr == NULL)
		ft_error(MLX, cub);
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_W, WIN_H, "CUB3D");
	if (cub->win_ptr == NULL)
		ft_error(WINDOW, cub);
	cub->img_w = WIN_W;
	cub->img_h = WIN_H;
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
	if (!cub->img)
		ft_error(CUBIMG, cub);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel,
			&cub->line_length, &cub->endian);
	cub->player = init_player(cub);
	init_position(cub);
	textures_definer(cub);
	return (0);
}

t_player *init_player(t_data *cub)
{
	t_player *player;
	
	player = (t_player *) malloc(sizeof(t_player) * 1);
	if (player == NULL)
		ft_error(PLAYER, cub);
	//init_map(cub);
	player->pov = (t_pov *) malloc(sizeof(t_pov) * 1);
	init_orientation(player, cub->player_init_ori);
	init_camera(player, cub);
	

	return (player);
}

void init_orientation(t_player *player, char player_init_ori)
{
	player->fov = FOV;
	if (player_init_ori == 'N')
		player->p_ang = -90 * DG_RAD;
	else if (player_init_ori == 'E')
		player->p_ang = 0 * DG_RAD;
	else if (player_init_ori == 'O')
		player->p_ang = 180 * DG_RAD;
	else
		player->p_ang = 90 * DG_RAD;
	player->pov->dirX = cos(player->p_ang);
	player->pov->dirY = sin(player->p_ang);
}

void init_position(t_data *cub)
{

	cub->player->posX = (double) cub->init_x + 0.5;
	cub->player->posY = (double) cub->init_y + 0.5;
	
	// y = 0;
	// x = 0;
	// PRINT_COLOR_MAP(cub);
	// while (y < cub->map_h)
	// {
	// 	x = 0;
	// 	while (x < cub->map_w && cub->map[y][x] != 0 && cub->map[y][x] != '\n')
	// 	{
	// 		if (cub->map[y][x] > 49)
	// 		{
	// 			cub->player->posX = x + 0.5;
	// 			cub->player->posY = y + 0.5;
	// 			cub->map[y][x] = '0';
	// 			break;
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }
	return ;
}

void init_camera(t_player *player, t_data *cub)
{
	player->cam = (t_camera *) malloc(sizeof(t_camera) * 1);
	if (player->cam == NULL)
		ft_error(CAMERA, cub);
	player->cam->planeX = -player->pov->dirY * tan(player->fov / 2);
	player->cam->planeY = player->pov->dirX * tan(player->fov / 2);
}

void init_map(t_data *cub)
{
	int 	**map;
	int		i;
	int		j;
	int 	c_map[4][4] = {{1, 1, 1, 1},{1, 1, 0, 1}, {1, 0, 'E', 1}, {1, 1, 1, 1}};

	i = 0;	
	map = ft_calloc(4, sizeof(int *));
	while (i < 4)
	{
		map[i] = ft_calloc(4, sizeof(int));
		j = 0;
		while (j < 4)
		{
			map[i][j] = c_map[i][j];
			j++;
		}
		i++;
	}
	cub->map = map;
	cub->map_h = 4;
	cub->map_w = 4;
	cub->player_init_ori = 'E';
	
}

void init_textures_to_null(t_data *cub)
{
	cub->north = NULL;
	cub->south = NULL;
	cub->west = NULL;
	cub->east = NULL;
	cub->in_map = false;
}

void textures_definer(t_data *cub)
{
	cub->texNorth.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./refs/redbrick.xpm", &cub->texNorth.width,
			&cub->texNorth.height);
	cub->texNorth.data = mlx_get_data_addr(cub->texNorth.img,
			&cub->texNorth.bits_per_pixel, &cub->texNorth.line_length, 
			&cub->texNorth.endian);
	cub->texSouth.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./refs/mossy.xpm", &cub->texSouth.width,
			&cub->texSouth.height);
	cub->texSouth.data = mlx_get_data_addr(cub->texSouth.img, 
			&cub->texSouth.bits_per_pixel, &cub->texSouth.line_length, 
			&cub->texSouth.endian);
	cub->texEast.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./refs/greystone.xpm", &cub->texEast.width,
			&cub->texEast.height);
	cub->texEast.data = mlx_get_data_addr(cub->texEast.img, 
			&cub->texEast.bits_per_pixel, &cub->texEast.line_length, 
			&cub->texEast.endian);
	cub->texWest.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./refs/colorstone.xpm", &cub->texWest.width,
			&cub->texWest.height);
	cub->texWest.data = mlx_get_data_addr(cub->texWest.img, 
			&cub->texWest.bits_per_pixel, &cub->texWest.line_length, 
			&cub->texWest.endian);
}
	