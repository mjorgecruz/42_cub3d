/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window_bonus3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:01:54 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 14:06:32 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_keys(t_data *cub);
void	texture_door_bonus(t_data *cub);
void	init_position_bonus(t_data *cub, int i, int j);
void	init_fires_bonus(t_data *cub, int count);
void	fill_fire_info_bonus(t_data *cub, int num, int i, int j);

void	init_keys(t_data *cub)
{
	cub->keys.back_front = 0;
	cub->keys.left_right = 0;
	cub->keys.rotate = 0;
}

void	texture_door_bonus(t_data *cub)
{
	int	fd;

	fd = open("./textures/Door.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(20, cub);
	close(fd);
	cub->door.img = mlx_xpm_file_to_image(cub->mlx_ptr,
			"./textures/Door.xpm", &cub->door.width,
			&cub->door.height);
	if (cub->door.img == NULL)
		ft_error(1000, cub);
	cub->door.data = mlx_get_data_addr(cub->door.img, \
			&cub->door.bits_per_pixel, &cub->door.line_length, \
			&cub->door.endian);
}

void	init_position_bonus(t_data *cub, int i, int j)
{
	int	count_doors;
	int	count_fires;

	count_doors = 0;
	count_fires = init_pos_bonus_helper(cub);
	while (++i < cub->map_h)
	{
		j = -1;
		while (++j < cub->map_w)
		{
			if (cub->map[i][j] == 'D'
				&& ((cub->map[i + 1][j] == '1' && cub->map[i - 1][j] == '1') \
				|| (cub->map[i][j + 1] == '1' && cub->map[i][j - 1] == '1')))
				count_doors++;
			else if (cub->map[i][j] == 'D')
				cub->map[i][j] = '0';
			else if (cub->map[i][j] == 'F')
				count_fires++;
		}
	}
	if (count_doors > 0)
		init_doors_bonus(cub, count_doors);
	if (count_fires > 0)
		init_fires_bonus(cub, count_fires);
	return ;
}

void	init_fires_bonus(t_data *cub, int count)
{
	int	i;
	int	j;
	int	fire_num;

	fire_num = 0;
	cub->fires = (t_fire *)malloc((count + 1) * sizeof(t_fire));
	if (cub->fires == NULL)
		ft_error(150, cub);
	i = -1;
	while (++i < cub->map_h)
	{
		j = -1;
		while (++j < cub->map_w)
		{
			if (cub->map[i][j] == 'F')
			{
				fill_fire_info_bonus(cub, fire_num, i, j);
				fire_num++;
			}
		}
	}
	cub->fires[count].pos_x = -1;
	cub->fires[count].pos_y = -1;
}

void	fill_fire_info_bonus(t_data *cub, int num, int i, int j)
{
	cub->fires[num].pos_x = (double) j + 0.5;
	cub->fires[num].pos_y = (double) i + 0.5;
	cub->fires[num].drawn = 0;
}
