/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:09:53 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/14 15:39:47 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void PRINT_COLOR_MAPCPY(t_data *cub);
void PRINT_COLOR_MAP(t_data *cub);
void color_select(int i);
void print_scenics(t_data *cub);

void print_scenics(t_data *cub)
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
}

void color_select(int i)
{
    // if (i == ' ')
    //     ft_printf("\033[37mS\033[0m"); // White
    // else if (i == '1')
    //     ft_printf("\033[1;32m1\033[0m"); // Bold Green
    // else if (i == 'N' || i == 'W' || i == 'E' || i == 'S')
    //     ft_printf("\033[1;31mN\033[0m"); // Bold Red
    // else if (i == '0')
    //     ft_printf("\033[33m0\033[0m"); // Yellow
    // else if (i == 0)
    //     ft_printf("\033[35mE\033[0m"); // Magenta (other color)
    // else
        ft_printf("\033[31mX %i \033[0m", i); // Red
}

void PRINT_COLOR_MAP(t_data *cub)
{

	ft_printf("\n[ORIGINAL MAP]\n");
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
	ft_printf("ORIGINAL MAP PRINTED\n");
}

void PRINT_COLOR_MAPCPY(t_data *cub)
{

	ft_printf("\n[MAP COPY:]\n");
	int i = 0;
	int j;
	while (i < cub->map_h)
	{
		j = 0;
		while (j < cub->map_w)
		{
			color_select(cub->map_cpy[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("MAP COPY PRINTED\n");
}