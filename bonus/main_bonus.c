/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/19 15:21:17 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_data	cub;
	
	field_filler(&cub);
	check_user_input(argc, argv[1], &cub);
	read_mapfile(&cub, argv[1]);
	read_lines(&cub);
	parser_first(&cub);	
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
	cub->fire1.data = NULL;
	cub->fire1.img = NULL;
	cub->fire2.data = NULL;
	cub->fire2.img = NULL;
	cub->fire3.data = NULL;
	cub->fire3.img = NULL;
	cub->north = NULL;
	cub->south = NULL;
	cub->east = NULL;
	cub->west = NULL;
	cub->map = NULL;
	cub->map_cpy = NULL;
	cub->player = NULL;
	cub->doors = NULL;
	cub->fires = NULL;
}
