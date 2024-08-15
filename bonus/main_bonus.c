/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/15 13:53:27 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

void	window_updater(t_data *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img);
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
}

int	main(int argc, char **argv)
{
	t_data	cub;

	tex_preparer(&cub);
	check_user_input(argc, argv[1], &cub);
	cub.map_h = 0;
	cub.map_w = 0;
	cub.count[0] = 0;
	cub.count[1] = 0;
	cub.count[2] = 0;
	cub.count[3] = 0;
	cub.count[4] = 0;
	cub.count[5] = 0;
	cub.l_start = 0;
	cub.init_x = -1;
	cub.init_y = -1;
    cub.lc = 0;
	cub.line = NULL;
	cub.in_map = false;
	read_mapfile(&cub, argv[1]);
	read_lines(&cub);
	parser_first(&cub);	
	init_fields(&cub);
	run_window(&cub);
	general_free(&cub);
	return (0);
}

void tex_preparer(t_data *cub)
{
	cub->texEast.data = NULL;
	cub->texNorth.data = NULL;
	cub->texSouth.data = NULL;
	cub->texWest.data = NULL;
	cub->texEast.img = NULL;
	cub->texNorth.img = NULL;
	cub->texSouth.img = NULL;
	cub->texWest.img = NULL;
	cub->north = NULL;
	cub->south = NULL;
	cub->east = NULL;
	cub->west = NULL;
	cub->map = NULL;
	cub->map_cpy = NULL;
	cub->player = NULL;
	
}
