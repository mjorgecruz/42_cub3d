/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:23:03 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/01 11:51:50 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void check_duplicates(t_data *cub, int id);
void fill_counter(t_data *cub, int id);
void save_path(char *line, t_data *cub, int id);
void save_rgb(char *line, t_data *cub, int id);
void get_scenic_id(char *str, t_data *cub);
void read_mapfile(t_data *cub, char *filename);

bool is_empty_line(char *str)
{
    int i;

    i = 0;
    i = jump_whitepaces(str);
    if (str[i -1] == '\n')
        return (true);
    else
        return (false);
}

void check_duplicates(t_data *cub, int id)
{
    if (cub->count[id] == 1)
    {
        ft_printf("(NEDDS TO BE CORRECTED) Duplicate FOUND CODE = %i \n");
        exit(EXIT_FAILURE);
    }
}

void fill_counter(t_data *cub, int id)
{
    check_duplicates(cub, id);
    cub->count[id] = 1;
}

void save_path(char *line, t_data *cub, int id)
{
    int i;
    i = jump_whitepaces(line);
    fill_counter(cub, id);
    if (id == NORTH)
        cub->north = ft_strdup(line + i);
    else if (id == SOUTH)
        cub->east = ft_strdup(line + i);
    else if (id == WEST)
        cub->west = ft_strdup(line + i);
    else if (id == EAST)
        cub->east = ft_strdup(line + i);
    ft_printf("[SAVEDPATH =]%s[END]\n");
}

void save_rgb(char *line, t_data *cub, int id)
{
    int i;

    i = jump_whitepaces(line);
    fill_counter(cub, id);
    
    //pegar nos valores e separar por espacos e virgulas
    //guardars os na estrutura
    
    if (id == CEILING)
    {   
        cub->cl_rgb[0] = 100;
        cub->cl_rgb[1] = 120;
        cub->cl_rgb[2] = 160;
    }
    else if (id == FLOOR)
    {   
        cub->cl_rgb[0] = 111;
        cub->cl_rgb[1] = 222;
        cub->cl_rgb[2] = 033;
    }
}

void get_scenic_id(char *str, t_data *cub)
{
    if (is_empty_line(str) == true)
        return ;
    else if (ft_strncmp(str, "NO ", 3) == 0)
        save_path(str + 3, cub, NORTH);
    else if (ft_strncmp(str, "SO ", 3) == 0)
        save_path(str + 3, cub, SOUTH);
    else if (ft_strncmp(str, "WE ", 3) == 0)
        save_path(str + 3, cub, WEST);
    else if (ft_strncmp(str, "EA ", 3) == 0)
        save_path(str + 3, cub, EAST);
    else if (ft_strncmp(str, "F ", 2) == 0)
        save_rgb(str, cub, FLOOR);
    else if (ft_strncmp(str, "C ", 2) == 0)
        save_rgb(str, cub, CEILING);
    else
    {
        ft_printf("ERROR IN THE HEADER\n");
        exit(EXIT_FAILURE);
    }
}

void read_mapfile(t_data *cub, char *filename)
{
    int fd;
    char *line;
    
    fd = open(filename, O_RDONLY, 0);
    is_fd_invalid(fd, cub);
    ft_printf("[IN F(READMAP)] \n");
    
    
    while ((line = get_next_line(fd)) != NULL)
    {
        //verificar quando mapa
        get_scenic_id((line + jump_whitepaces(line)), cub); //still have to check path format and to transform color strings into integers

        //NEED TO get tha fukin mappppppp into a matrix

        free(line);
    }
    close (fd);
    ft_printf("[OUT F(READMAP)]\n");
}
