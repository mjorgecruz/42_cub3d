/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:57:55 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 13:00:08 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int			init_fields_bonus(t_data *cub);
t_player	*init_player(t_data *cub);
void		init_orientation(t_player *player, char player_init_ori);
void		init_doors_bonus(t_data *cub, int count);
void		fill_door_info_bonus(t_data *cub, int door_num, int i, int j);

int	init_fields_bonus(t_data *cub)
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
	init_position_bonus(cub);
	init_keys(cub);
	textures_definer_bonus(cub);
	return (0);
}

t_player	*init_player(t_data *cub)
{
	t_player	*player;

	player = (t_player *) malloc(sizeof(t_player) * 1);
	if (player == NULL)
		ft_error(PLAYER, cub);
	player->pov = (t_pov *) malloc(sizeof(t_pov) * 1);
	init_orientation(player, cub->player_init_ori);
	init_camera(player, cub);
	return (player);
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

void	init_doors_bonus(t_data *cub, int count)
{
	int	i;
	int	j;
	int	door_num;

	door_num = 0;
	cub->doors = (t_door *)malloc((count + 1) * sizeof(t_door));
	if (cub->doors == NULL)
		ft_error(125, cub);
	i = -1;
	while (++i < cub->map_h)
	{
		j = -1;
		while (++j < cub->map_w)
		{
			if (cub->map[i][j] == 'D')
			{
				fill_door_info_bonus(cub, door_num, i, j);
				door_num++;
			}
		}
	}
	cub->doors[count].orientation = -1;
}

void	fill_door_info_bonus(t_data *cub, int door_num, int i, int j)
{
	cub->doors[door_num].pos_x = (double) j + 0.5;
	cub->doors[door_num].pos_y = (double) i + 0.5;
	if (cub->map[i + 1][j] == '1' && cub->map[i - 1][j] == '1')
		cub->doors[door_num].orientation = 1;
	else if (cub->map[i][j - 1] == '1' && cub->map[i][j + 1] == '1')
		cub->doors[door_num].orientation = 0;
	cub->doors[door_num].open = false;
	cub->doors[door_num].status = 0;
	cub->doors[door_num].speed = 0.002;
	cub->doors[door_num].last_time = get_time();
	cub->doors[door_num].position = 0.0;
}
