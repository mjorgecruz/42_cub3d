/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:00 by masoares          #+#    #+#             */
/*   Updated: 2024/08/19 15:51:08 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	run_window_bonus(t_data *cub)
{
	mlx_loop_hook(cub->mlx_ptr, render_bonus, cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, key_detect, cub);
	mlx_hook(cub->win_ptr, KeyRelease, KeyReleaseMask, key_undetect, cub);
	mlx_hook(cub->win_ptr, DestroyNotify, NoEventMask, close_win_free, cub);
	mlx_hook(cub->win_ptr, 6, 1L << 6, &handle_mouse_move, cub);
	mlx_loop(cub->mlx_ptr);
}

int render_bonus(t_data *cub)
{
	int i;
	
	i = 0;
	check_dirs(cub);
	check_rots(cub);
	update_fire(cub);
	if (cub->doors)
	{
		while (cub->doors[i].orientation >= 0)
			update_door_position(&(cub->doors[i++]));
	}
	mlx_destroy_image(cub->mlx_ptr, cub->img);
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
	render_cel_gr(cub);
	display_bonus(cub);
	minimaper_bonus(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
	return(0);
}

void	render_cel_gr(t_data *cub)
{
	int x;
	int y;
	int c_color;
	int g_color;
	
	x = 0;
	y = 0;
	g_color = (cub->fl_rgb[0]<< 16) + (cub->fl_rgb[1] << 8) + cub->fl_rgb[2];
	c_color = (cub->cl_rgb[0]<< 16) + (cub->cl_rgb[1] << 8) + cub->cl_rgb[2];
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
			pixel_put(cub, x++, y, c_color);
		y++;
	}
	while (y <= WIN_H)
	{
		x = 0;
		while (x < WIN_W)
			pixel_put(cub, x++, y, g_color);
		y++;
	}
}

void	check_dirs(t_data *cub)
{
	if (cub->keys.back_front == 1)
		control_trans(cub, 1);
	if (cub->keys.back_front == -1)
		control_trans(cub, -1);
	if (cub->keys.left_right == 1)
		control_sides(cub, 1);
	if (cub->keys.left_right == -1)
		control_sides(cub, -1);
}
	
void	check_rots(t_data *cub)
{
	if (cub->keys.rotate == 1)
		control_rot(cub, 1);
	if (cub->keys.rotate == -1)
		control_rot(cub, -1);
}