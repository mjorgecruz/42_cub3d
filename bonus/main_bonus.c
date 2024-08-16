/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/16 13:46:33 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_data	cub;

	tex_preparer(&cub);
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
	check_user_input(argc, argv[1], &cub);
	read_mapfile(&cub, argv[1]);
	read_lines(&cub);
	parser_first_bonus(&cub);	
	init_fields_bonus(&cub);
	run_window_bonus(&cub);
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
	cub->door.data = NULL;
	cub->door.img = NULL;
	cub->north = NULL;
	cub->south = NULL;
	cub->east = NULL;
	cub->west = NULL;
	cub->map = NULL;
	cub->map_cpy = NULL;
	cub->player = NULL;
	cub->doors = NULL;
}
