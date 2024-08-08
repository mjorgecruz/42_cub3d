/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/08 16:16:12 by luis-ffe         ###   ########.fr       */
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
	
	ft_printf("F: [%i][%i][%i]\n", cub->fl_rgb[0], cub->fl_rgb[1], cub->fl_rgb[2]);
	ft_printf("C: [%i][%i][%i]\n", cub->cl_rgb[0], cub->cl_rgb[1], cub->cl_rgb[2]);
	
	// ft_printf("[MAPA MATRIX:]\n");
	// int i = 0;
	// int j;
	// while (i < cub->map_h)
	// {
	// 	j = 0;
	// 	while (j < cub->map_w)
	// 	{
	// 		ft_printf("[%i]", cub->map[i][j]);
	// 		j++;
	// 	}
	// 	ft_printf("\n");
	// 	i++;
	// }
	// ft_printf("POPOTA SEXY\n");
}

void color_select(int i)
{
    if (i == ' ')
        ft_printf("\033[37mS\033[0m"); // White
    else if (i == '1')
        ft_printf("\033[1;32m1\033[0m"); // Bold Green
    else if (i == 'N')
        ft_printf("\033[1;31mN\033[0m"); // Bold Red
    else if (i == '0')
        ft_printf("\033[33m0\033[0m"); // Yellow
    else if (i == 0)
        ft_printf("\033[35mE\033[0m"); // Magenta (other color)
    else
        ft_printf("\033[31mX\033[0m"); // Red
}

void COLOR_MAP(t_data *cub)
{

	ft_printf("[MAPA LGBTQ+:]\n");
	int i = 0;
	int j;
	while (i < cub->map_h)
	{
		j = 0;
		while (j < cub->map_w)
		{
			color_select(cub->map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("POPOTA SEXY CANIONA\n");
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
	cub.l_start = 0;
	cub.init_x = -1;
	cub.init_y = -1;
    cub.lc = 0;
	cub.line = NULL;
	cub.in_map = false;

	read_mapfile(&cub, argv[1]);
	get_map_size(&cub);
	read_lines(&cub);
	build_map(&cub);
	parser_first(&cub);

	/* Reads entire file ito a single string and splits it by newlines*/
	// ft_printf("\n\n----------------------1 ---------------------\n\n");
	// read_mapfile(&cub, argv[1]);
	
	// ft_printf("\n\n----------------------2 ---------------------\n\n");
	// get_map_size(&cub);
	// /* newline a meio do mapa ou um enter empty line valido?*/
	
	// ft_printf("\n\n----------------------3 ---------------------\n\n");
	// read_lines(&cub);
	
	// ft_printf("\n\n----------------------4 ---------------------\n\n");
	// build_map(&cub);
	// tester_print(&cub);


	// ft_printf("\n\n----------------------5 ---------------------\n\n");
	// COLOR_MAP(&cub);
	
	// parser_first(&cub);
	
	// COLOR_MAP(&cub);

	// tester_print(&cub);
	// init_fields(&cub);
	// run_window(&cub);
}

	// read_mapfile(&cub, argv[1]);
	// get_map_size(&cub);
	// read_lines(&cub);
	// build_map(&cub);
	// parser_first(&cub);
	