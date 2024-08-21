/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:26:15 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 14:42:01 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	textures_definer_bonus_tex(cub);
}

void	texture_fire_bonus(t_data *cub)
{
	int	fd;

	fd = open("./textures/fire1.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(MISSTEXT, cub);
	close(fd);
	fd = open("./textures/fire2.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(MISSTEXT, cub);
	close(fd);
	fd = open("./textures/fire3.xpm", O_RDONLY, 0);
	if (fd < 0)
		ft_error(MISSTEXT, cub);
	close(fd);
	texture_fire_bonus_tex(cub);
	cub->fire_num = 0;
	cub->fire_last_time = 0.0;
}

int	init_pos_bonus_helper(t_data *cub)
{
	cub->player->posx = (double)cub->init_x + 0.5;
	cub->player->posy = (double)cub->init_y + 0.5;
	return (0);
}
