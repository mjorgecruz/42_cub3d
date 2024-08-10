/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/10 21:19:08 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	window_updater(t_data *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img);
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
}

int	main(int argc, char **argv)
{
	t_data	cub;
	(void) argc;
	(void) argv;

	// check_user_input(argc, argv[1], &cub);
	// /*testing GNL */
	
	// ft_printf("[1]\n");
	// read_mapfile(&cub, argv[1]);
	// ft_printf("[2]\n");
	
	/*coment this up here if you need */	
	init_fields(&cub);
	t_img north;
	t_img south;
	t_img east;
	t_img west;
	north.img = mlx_xpm_file_to_image(cub.mlx_ptr,
			"./refs/bluestone.xpm", &north.width,
			&north.height);	
	south.img = mlx_xpm_file_to_image(cub.mlx_ptr,
			"./refs/eagle.xpm", &south.width,
			&south.height);	
	east.img = mlx_xpm_file_to_image(cub.mlx_ptr,
			"./refs/greystone.xpm", &east.width,
			&east.height);
	west.img = mlx_xpm_file_to_image(cub.mlx_ptr,
			"./refs/redbrick.xpm", &west.width,
			&west.height);
	
	run_window(&cub);
}
