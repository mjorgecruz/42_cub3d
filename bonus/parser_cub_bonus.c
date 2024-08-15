/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:30:36 by masoares          #+#    #+#             */
/*   Updated: 2024/08/15 22:08:05 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
                cub->player_init_ori = cub->map[j][i];
                cub->map[i][j] = '0';
                dup++;
            }
		}
	}
    if (dup != 1)
        ft_error(11, cub);
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
                ft_error(12, cub);
            return ;
        }
        i++;
    }
}

int floodfill_bonus(t_data *cub, int x, int y, int targ, int new)
{
    int current;
    int ret;

    ret = 0;
    if (x < 0 || x >= cub->map_w || y < 0 || y >= cub->map_h) 
        return 0;
    current = cub->map_cpy[y][x];
    if (current == 49)
        return 1;
    if (current != targ && !is_valid_orient(current) && current != 'D')
        return 0;
    cub->map_cpy[y][x] = new;
    ret += floodfill_bonus(cub, x - 1, y, targ, new);
    ret += floodfill_bonus(cub, x + 1, y, targ, new);
    ret += floodfill_bonus(cub, x, y - 1, targ, new);
    ret += floodfill_bonus(cub, x, y + 1, targ, new);
    if (ret == 4)
        return 1;
    return 0;
}

void parser_first_bonus(t_data *cub)
{
    get_map_size(cub);
    build_map(cub);
    make_map_copy(cub); 
    get_player_pos(cub);
    if (floodfill_bonus(cub, cub->init_x, cub->init_y, 48, 49) == 0)
    {
        ft_error(11, cub);
        return ;
    }
    PRINT_COLOR_MAP(cub);
    PRINT_COLOR_MAPCPY(cub);
    return ; //passes returns 0
}