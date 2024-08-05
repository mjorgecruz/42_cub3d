/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:23:03 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/05 10:54:22 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool is_empty_line(char *str);
bool is_valid_element(int c);
bool has_reached_map(char *line, t_data *cub);
//void    build_map(t_data *cub, char *line);
void get_map_size(t_data *cub);

void check_duplicates(t_data *cub, int id);
void fill_counter(t_data *cub, int id);
void save_path(char *line, t_data *cub, int id);
void save_rgb(char *line, t_data *cub, int id);
void get_scenic_id(t_data *cub, int i);
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

    ft_printf("PATH SAVED = \n", line);
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
    //int i;

    //i = jump_whitepaces(line);
    fill_counter(cub, id);
    (void) line;
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

void get_scenic_id(t_data *cub, int i)
{
    int w;
    ft_printf("\nENTERED SCENICS GETTER\n");

    w = jump_whitepaces(cub->line[i]); 
    if (is_empty_line(cub->line[i]) == true)
        return ;
    else if (ft_strncmp((cub->line[i] + w), "NO ", 3) == 0)
        save_path((cub->line[i] + w + 3), cub, NORTH);
    else if (ft_strncmp((cub->line[i] + w), "SO ", 3) == 0)
        save_path((cub->line[i] + w + 3), cub, SOUTH);
    else if (ft_strncmp((cub->line[i] + w), "WE ", 3) == 0)
        save_path((cub->line[i] + w + 3), cub, WEST);
    else if (ft_strncmp((cub->line[i] + w), "EA ", 3) == 0)
        save_path((cub->line[i] + w + 3), cub, EAST);
    else if (ft_strncmp((cub->line[i] + w), "F ", 2) == 0)
        save_rgb((cub->line[i]), cub, FLOOR);
    else if (ft_strncmp((cub->line[i] + w), "C ", 2) == 0)
        save_rgb((cub->line[i]), cub, CEILING);
    else
    {
        ft_printf("ERROR IN THE HEADER\n");
        exit(EXIT_FAILURE);
    }
}

bool is_valid_element(int c)
{
    if  (!ft_iswhitespace(c))
    {
        if (c != '1' && c != '0' && c!= 'N')
            return (false);
    }
    return (true);
}

bool has_reached_map(char *line, t_data *cub)
{
    int i;

    i = 0;
    if (cub->in_map == true)
        return (true);
    else if (is_empty_line(line))
        return (false);

    while (line[i] && line[i] != '\n')
    {
        if (!is_valid_element(line[i]))
            return (false);
        i++;
    }
    if (line[i] == '\n' && i != 0)
    {
        cub->in_map = true;
        return (true);
    }
    return (true);
}

// void    build_map(t_data *cub, char *line)
// {
//     int len;
    
//     len = ft_strlen(line);
// }

void get_map_size(t_data *cub)
{
    int i;
    int size;

    i = 0;
    while (cub->lc > i)
    {
        if (cub->in_map == false)
            has_reached_map(cub->line[i], cub);
        else if (cub->in_map == true)
        {
            size = ft_strlen(cub->line[i]);
            if (cub->map_w < size)
                cub->map_w = size;
            cub->map_h++;
        }
        i++;
    }
}

/*
reads entire file to one string line
splits it by newlines
possible problems:

STRJOIN: possible leaks
SPLIT: possible leaks
*/
void read_mapfile(t_data *cub, char *filename)
{
    int fd;
    char *temp;
    char *content;
    
    fd = open(filename, O_RDONLY, 0);
    is_fd_invalid(fd, cub);
    while ((temp = get_next_line(fd)))
    {
        cub->lc++;
        content = ft_strjoin(content, temp);
        free(temp);
    }
    close (fd);
    cub->line = ft_split(content, '\n');
    ft_printf("READMAP %s", content);
    ft_printf("\nLC = %i\n", cub->lc);

    free(content);
}


void read_lines(t_data *cub)
{
    int i;

    i = 0;
    ft_printf("memememe :    %s", cub->line[i]);
    while (cub->line[i])
    {
        if (cub->in_map == false)
            has_reached_map(cub->line[i], cub);
        else if (cub->in_map == false) 
            get_scenic_id(cub, i);
        // else if (cub->in_map == true)
        // {
        //     //build the matrix here( needs to know total map length and total map height)
        // }
        i++;
    }
}
