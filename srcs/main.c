/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/05 14:38:04 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	window_updater(t_data *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img);
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
}

void tester_print(t_data *cub)
{
	ft_printf("MAP H: [%i]\n", cub->map_h);
	ft_printf("MAP W: [%i]\n", cub->map_w);
	ft_printf("MAP SCENICS: [%i] [%i] [%i] [%i] [%i] [%i]\n", cub->count[0], cub->count[1], cub->count[2], cub->count[3], cub->count[4], cub->count[5]);
	ft_printf("PATH NO: [%s]\n", cub->north);
	ft_printf("PATH SO: [%s]\n", cub->south);
	ft_printf("PATH WE: [%s]\n", cub->west);
	ft_printf("PATH EA: [%s]\n", cub->east);
}


int	main(int argc, char **argv)
{
	t_data	cub;

	check_user_input(argc, argv[1], &cub);
	
	cub.map_h = 0;
	cub.map_w = 0;
	cub.count[0] = 0;
	cub.count[1] = 0;
	cub.count[2] = 0;
	cub.count[3] = 0;
	cub.count[4] = 0;
	cub.count[5] = 0;
    cub.lc = 0;
	cub.line = NULL;
	cub.in_map = false;                //initialize this as false please
	
	ft_printf("\n\n----------------------1 ---------------------\n\n");
	read_mapfile(&cub, argv[1]);
	ft_printf("\n\n----------------------2 ---------------------\n\n");
	get_map_size(&cub);
	/* newline a meio do mapa ou um enter empty line valido?*/
	ft_printf("\n\n----------------------3 ---------------------\n\n");
	read_lines(&cub);
	ft_printf("\n\n----------------------4 ---------------------\n\n");
	tester_print(&cub);
	ft_printf("\n\n----------------------5 ---------------------\n\n");

	// init_fields(&cub);
	// run_window(&cub);
}
