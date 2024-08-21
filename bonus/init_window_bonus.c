/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:26 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 13:13:42 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_camera(t_player *player, t_data *cub);
void	textures_definer_bonus(t_data *cub);
void	texture_fire_bonus(t_data *cub);
int		init_pos_bonus_helper(t_data *cub);

void	init_camera(t_player *player, t_data *cub)
{
	player->cam = (t_camera *) malloc(sizeof(t_camera) * 1);
	if (player->cam == NULL)
		ft_error(CAMERA, cub);
	player->cam->planex = -player->pov->diry * tan(player->fov / 2);
	player->cam->planey = player->pov->dirx * tan(player->fov / 2);
}

void	textures_definer_bonus(t_data *cub)
{
	cub->texnorth.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->north, &cub->texnorth.width,
			&cub->texnorth.height);
	cub->texnorth.data = mlx_get_data_addr(cub->texnorth.img,
			&cub->texnorth.bits_per_pixel, &cub->texnorth.line_length, \
			&cub->texnorth.endian);
	cub->texsouth.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->south, &cub->texsouth.width,
			&cub->texsouth.height);
	cub->texsouth.data = mlx_get_data_addr(cub->texsouth.img, \
			&cub->texsouth.bits_per_pixel, &cub->texsouth.line_length, \
			&cub->texsouth.endian);
	cub->texeast.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->east, &cub->texeast.width,
			&cub->texeast.height);
	cub->texeast.data = mlx_get_data_addr(cub->texeast.img, \
			&cub->texeast.bits_per_pixel, &cub->texeast.line_length, \
			&cub->texeast.endian);
	cub->texwest.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			cub->west, &cub->texwest.width,
			&cub->texwest.height);
	cub->texwest.data = mlx_get_data_addr(cub->texwest.img, \
			&cub->texwest.bits_per_pixel, &cub->texwest.line_length, \
			&cub->texwest.endian);
	texture_door_bonus(cub);
	texture_fire_bonus(cub);
}

void	texture_fire_bonus(t_data *cub)
{
	int	fd;

	fd = open("./textures/fire1.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(20, cub);
	close(fd);
	fd = open("./textures/fire2.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(20, cub);
	close(fd);
	fd = open("./textures/fire3.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(20, cub);
	close(fd);
	cub->fire1.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/fire1.xpm", &cub->fire1.width,
			&cub->fire1.height);
	if (cub->fire1.img == NULL)
		ft_error(1000, cub);
	cub->fire1.data = mlx_get_data_addr(cub->fire1.img, \
			&cub->fire1.bits_per_pixel, &cub->fire1.line_length, \
			&cub->fire1.endian);
	cub->fire2.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/fire2.xpm", &cub->fire2.width,
			&cub->fire2.height);
	if (cub->fire2.img == NULL)
		ft_error(1000, cub);
	cub->fire2.data = mlx_get_data_addr(cub->fire2.img, \
			&cub->fire2.bits_per_pixel, &cub->fire2.line_length, \
			&cub->fire2.endian);
	cub->fire3.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/fire3.xpm", &cub->fire3.width,
			&cub->fire3.height);
	if (cub->fire3.img == NULL)
		ft_error(1000, cub);
	cub->fire3.data = mlx_get_data_addr(cub->fire3.img, \
			&cub->fire3.bits_per_pixel, &cub->fire3.line_length, \
			&cub->fire3.endian);
	cub->fire_num = 0;
	cub->fire_last_time = 0.0;
}

int	init_pos_bonus_helper(t_data *cub)
{
	cub->player->posx = (double)cub->init_x + 0.5;
	cub->player->posy = (double)cub->init_y + 0.5;
	return (0);
}
