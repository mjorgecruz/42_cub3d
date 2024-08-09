/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:00 by masoares          #+#    #+#             */
/*   Updated: 2024/08/09 22:59:30 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	run_window(t_data *cub)
{
	
	render(cub);
	// minimaper_initial(cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, key_detect, cub);
	mlx_hook(cub->win_ptr, DestroyNotify, NoEventMask, close_win_free, cub);
	mlx_loop(cub->mlx_ptr);
}

void render(t_data *cub)
{
	minimaper(cub);
}
