/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/13 10:38:28 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
	//printf("%c",cub.north[2]);
	run_window(&cub);
}
