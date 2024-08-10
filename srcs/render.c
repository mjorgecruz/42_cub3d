/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:00 by masoares          #+#    #+#             */
/*   Updated: 2024/08/10 18:58:52 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	display(cub);
	minimaper(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}
