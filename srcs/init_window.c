/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:26 by masoares          #+#    #+#             */
/*   Updated: 2024/08/17 10:32:24 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		init_fields(t_data *cub);
void	init_orientation(t_player *player, char player_init_ori);
void	init_position(t_data *cub);
void	init_camera(t_player *player, t_data *cub);
void	textures_definer(t_data *cub);

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

void	init_orientation(t_player *player, char player_init_ori)
{
	player->fov = FOV;
	if (player_init_ori == 'N')
		player->p_ang = -90 * DG_RAD;
	else if (player_init_ori == 'W')
		player->p_ang = 0 * DG_RAD;
	else if (player_init_ori == 'E')
		player->p_ang = 180 * DG_RAD;
	else
		player->p_ang = 90 * DG_RAD;
	player->pov->dirx = cos(player->p_ang);
	player->pov->diry = sin(player->p_ang);
}

void	init_position(t_data *cub)
{
	cub->player->posx = (double) cub->init_x + 0.5;
	cub->player->posy = (double) cub->init_y + 0.5;
	return ;
}

void	init_camera(t_player *player, t_data *cub)
{
	player->cam = (t_camera *) malloc(sizeof(t_camera) * 1);
	if (player->cam == NULL)
		ft_error(CAMERA, cub);
	player->cam->planex = -player->pov->diry * tan(player->fov / 2);
	player->cam->planey = player->pov->dirx * tan(player->fov / 2);
}

void	textures_definer(t_data *cub)
{
	cub->texnorth.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->north, &cub->texnorth.width,
			&cub->texnorth.height);
	cub->texnorth.data = mlx_get_data_addr(cub->texnorth.img,
			&cub->texnorth.bits_per_pixel, &cub->texnorth.line_length,
			&cub->texnorth.endian);
	cub->texsouth.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->south, &cub->texsouth.width,
			&cub->texsouth.height);
	cub->texsouth.data = mlx_get_data_addr(cub->texsouth.img,
			&cub->texsouth.bits_per_pixel, &cub->texsouth.line_length,
			&cub->texsouth.endian);
	cub->texeast.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->east, &cub->texeast.width,
			&cub->texeast.height);
	cub->texeast.data = mlx_get_data_addr(cub->texeast.img,
			&cub->texeast.bits_per_pixel, &cub->texeast.line_length,
			&cub->texeast.endian);
	cub->texwest.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->west, &cub->texwest.width,
			&cub->texwest.height);
	cub->texwest.data = mlx_get_data_addr(cub->texwest.img,
			&cub->texwest.bits_per_pixel, &cub->texwest.line_length,
			&cub->texwest.endian);
}
