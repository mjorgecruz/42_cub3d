/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:30:36 by masoares          #+#    #+#             */
/*   Updated: 2024/08/14 15:49:57 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void    get_player_pos(t_data *cub);
void    map_space(t_data *cub);
int     floodfill(t_data *cub, int x, int y, int targ, int new);
void    parser_first(t_data *cub);

void get_player_pos(t_data *cub)
{
	int i;
	int j;
    int dup;

    dup = 0;
    i = -1;
	while (++i < cub->map_h)
	{
		j = -1;
		while (++j < cub->map_w)
		{
			if (is_valid_orient(cub->map[i][j]))
            {
                cub->init_x = j;
                cub->init_y = i;
                cub->map[i][j] = '0';
                dup++;
            }
		}
	}
    if (dup != 1)
        exit(EXIT_FAILURE);
}

void    map_space(t_data *cub) //final do mapa com newlines
{
    int i;

    i = 1;
    while (i < cub->map_h - 1)
    {
        if (cub->map[i][0] == '\n')
        {
            while(cub->map[i][0] == '\n' && i < cub->map_h - 1)
                i++;
            if (i < cub->map_h - 1 && cub->map[i][0] != '\n')
            {   
                ft_printf("Invalid map\n");
                exit(EXIT_FAILURE);
            }
            return;
        }
        i++;
    }
}

int floodfill(t_data *cub, int x, int y, int targ, int new)
{
    int current;
    int ret;

    ret = 0;
    if (x < 0 || x >= cub->map_w || y < 0 || y >= cub->map_h) 
        return 0;
    current = cub->map_cpy[y][x];
    if (current == 49)
        return 1;
    if (current != targ && !is_valid_orient(current))
        return 0;

    cub->map_cpy[y][x] = new;
    ret += floodfill(cub, x - 1, y, targ, new);
    ret += floodfill(cub, x + 1, y, targ, new);
    ret += floodfill(cub, x, y - 1, targ, new);
    ret += floodfill(cub, x, y + 1, targ, new);
    if (ret == 4)
        return 1;
    return 0;
}

void parser_first(t_data *cub)
{
    get_map_size(cub);
    build_map(cub);
    make_map_copy(cub); // error and free case it cant
    get_player_pos(cub);
    
    ft_printf("Nx = %i\n", cub->init_x);
    ft_printf("Ny = %i\n", cub->init_y);

    if (floodfill(cub, cub->init_x, cub->init_y, 48, 49) == 0) //proper errors and frees
    {
        ft_printf("\033[1;31mFLOODFILL RESULT: \033[0m\n");///////////////////////////////////////////////
        PRINT_COLOR_MAPCPY(cub);//////////////////////////////////////////////////////////////////////////
        ft_printf("\033[1;31mMAPA DEU MERDA\033[0m\n");
        exit(EXIT_FAILURE);
        return ;
    }
    ft_printf("\n\033[1;32mFLOODFILL RESULT: \033[0m\n");/////////////////////////////////////////////////
    PRINT_COLOR_MAPCPY(cub);//////////////////////////////////////////////////////////////////////////////
    ft_printf("\n\033[1;32m!MAPA OK!\033[0m\n");
    return; //passes returns 0
}