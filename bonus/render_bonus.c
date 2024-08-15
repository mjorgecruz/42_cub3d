/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:00 by masoares          #+#    #+#             */
/*   Updated: 2024/08/15 21:12:58 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	run_window(t_data *cub)
{
	
	render(cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, key_detect, cub);
	mlx_hook(cub->win_ptr, DestroyNotify, NoEventMask, close_win_free, cub);
	mlx_loop(cub->mlx_ptr);
}

void render(t_data *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img);
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
	render_cel_gr(cub);
	display(cub);
	minimaper(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
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

