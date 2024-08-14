/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:23:03 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/14 13:39:27 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void check_scenics_count(t_data *cub);
void check_scenics(t_data *cub);
void check_duplicates(t_data *cub, int id);
void fill_counter(t_data *cub, int id);
void save_path(char *line, t_data *cub, int id);
void get_scenic_id(t_data *cub, int i);
bool has_reached_map(char *line, t_data *cub);
void read_mapfile(t_data *cub, char *filename);
void read_lines(t_data *cub);


void check_scenics_count(t_data *cub)
{
    int i;

    i = -1;
    while (++i <= 5)
    {
        if (cub->count[i] == 0)
        {
            ft_printf("\n MISSING SCENICS \n");
            exit(EXIT_FAILURE);
        }
    }
}

bool is_xpm_file(char *xpm)
{
    int i;

    i = 0;
    while(xpm[i])
    {
        if (xpm[i] == '.')
            if (!ft_strncmp(&xpm[i], ".xpm", 4))
            {
                if (is_empty_line(&xpm[i] + 4))
                    return (true);
            }
        i++;
    }
    return (false);
}

bool compare_id_xpm(char *xpm)
{
    if (!xpm)
        return (false);
    else if (!ft_strncmp(xpm, "south", 5))
        return (true);
    else if (!ft_strncmp(xpm, "north", 5))
        return (true); 
    else if (!ft_strncmp(xpm, "east", 4))
        return (true);
    else if (!ft_strncmp(xpm, "west", 4))
        return (true);
    return (false);
}

bool    check_texture_match(char *xpm)
{
    int i;
    int marker;
    
    marker = 0;
    i = -1;
    while (xpm[++i])
    {
        if (xpm[i] == '/')
            marker = i + 1;
    }
    if (!compare_id_xpm(xpm + marker))
        return (false);
    else
    if (!is_xpm_file(xpm + marker))
        return (false);
    return (true);
}

bool check_texture_str(char *xpm)
{
    int i;
    
    if (is_empty_line(xpm) || !xpm)
        return (false);
    i = 0;
    while (xpm[++i])
    {
        if(ft_iswhitespace(xpm[i]))
        {
            while (xpm[++i])
            {
                if(!ft_iswhitespace(xpm[i]))
                    return (false);   
            }
        }
    }
    if (!check_texture_match(xpm))
        return (false);
    return (true);
}

void check_xpm_format(t_data *cub)
{
    
    if (!check_texture_str(cub->north))
        exit(EXIT_FAILURE);
    else if (!check_texture_str(cub->east))
        exit(EXIT_FAILURE);
    else if (!check_texture_str(cub->south))
        exit(EXIT_FAILURE);
    else if (!check_texture_str(cub->west))
        exit(EXIT_FAILURE);    
}

void check_scenics(t_data *cub)
{
    check_scenics_count(cub);
    check_xpm_format(cub);
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
        cub->south = ft_strdup(line + i);
    else if (id == WEST)
        cub->west = ft_strdup(line + i);
    else if (id == EAST)
        cub->east = ft_strdup(line + i);
}

void get_scenic_id(t_data *cub, int i)
{
    char *p;

    p = cub->line[i];
    if (is_empty_line(p) == true)
        return ;
    else if (ft_strncmp((p + jump_whitepaces(p)), "NO ", 3) == 0)
        save_path(((p + jump_whitepaces(p)) + 3), cub, NORTH);
    else if (ft_strncmp((p + jump_whitepaces(p)), "SO ", 3) == 0)
        save_path(((p + jump_whitepaces(p)) + 3), cub, SOUTH);
    else if (ft_strncmp((p + jump_whitepaces(p)), "WE ", 3) == 0)
        save_path(((p + jump_whitepaces(p)) + 3), cub, WEST);
    else if (ft_strncmp((p + jump_whitepaces(p)), "EA ", 3) == 0)
        save_path(((p + jump_whitepaces(p)) + 3), cub, EAST);
    else if (ft_strncmp((p + jump_whitepaces(p)), "F ", 2) == 0)
        save_rgb((p + jump_whitepaces(p) + 2), cub, FLOOR);
    else if (ft_strncmp((p + jump_whitepaces(p)), "C ", 2) == 0)
        save_rgb(((p + jump_whitepaces(p)) + 2), cub, CEILING);
    else
    {
        ft_printf("ERROR IN THE HEADER\n");
        exit(EXIT_FAILURE);
    }
}

bool has_reached_map(char *line, t_data *cub)
{
    int i;

    i = 0;

    if (is_empty_line(line))
        return false;
    else if (!line[i] || line[i] == '\n')
        return (false);
    else if (cub->in_map == false)
    {
        while (line[i] == '1' || line[i] == '0' || line[i] == ' ')
            i++;
        if (line[i] == '\0' || line[i] == '\n')
            cub->in_map = true;
        return (true);
    }
    return (false);
}

void read_mapfile(t_data *cub, char *filename)
{
    int fd;
    char *temp;
    char *join;

    fd = open(filename, O_RDONLY, 0);
    is_fd_invalid(fd, cub);
    join = ft_strdup("");
    while ((temp = get_next_line(fd)))
    {
        cub->lc++;
        join = ft_strjoin(join, "*");
        join = ft_strjoin(join, temp);
        free(temp);
    }
    close (fd);
    cub->line = ft_split(join, '*');
    free(join);
}

void read_lines(t_data *cub)
{
    int i;

    i = 0;
    cub->in_map = false;
    while (cub->line[i] != NULL)
    {
        if (is_empty_line(cub->line[i]))
            i++;
        else
        {
            if (cub->in_map == false)
                has_reached_map(cub->line[i], cub);
            if (cub->in_map == false)
                get_scenic_id(cub, i);
            i++;
        }
    }
    //check other scenics here like if the xpm are correct
    //confirmar todos os elementos scenics
    check_scenics(cub);
    check_color_range(cub);
}
