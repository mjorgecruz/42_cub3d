/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:23:03 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/08 16:14:30 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int floodfill(t_data *cub, int x, int y, int targ, int new);
void map_space(t_data *cub);


void check_color_range(t_data *cub);
void get_rgb_fr_str(char *line, t_data *cub, int id);

bool is_empty_line(char *str);
bool is_valid_element(int c);
bool has_reached_map(char *line, t_data *cub);
void    build_map(t_data *cub);
void get_map_start(t_data *cub);
void get_map_size(t_data *cub);
void get_player_pos(t_data *cub);

void check_duplicates(t_data *cub, int id);
void fill_counter(t_data *cub, int id);
void save_path(char *line, t_data *cub, int id);
void save_rgb(char *line, t_data *cub, int id);
void get_scenic_id(t_data *cub, int i);
void read_mapfile(t_data *cub, char *filename);
void parser_first(t_data *cub);

bool is_empty_line(char *str)
{
    int i;

    i = 0;
    if (str == NULL || str[0] == '\0')
        return true;
    i = jump_whitepaces(str);
    if (str[i] == '\n' || str[i] == '\0')
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
        cub->south = ft_strdup(line + i);
    else if (id == WEST)
        cub->west = ft_strdup(line + i);
    else if (id == EAST)
        cub->east = ft_strdup(line + i);
}

/*if there are other things than numbers or whitspaces gives error 1
numbers separated by spaces error aswell
*/

int ft_confirm_line_rgb(char *color)
{
    int i;
    ft_printf("COR CARALHO: %s", color);
    
    if (!color)
        return 0;
    i = jump_whitepaces(color);
    while (color[i] && (color[i] >= '0' && color[i] <= '9'))
        i++;
    while (color[i])
    {
        if (!ft_iswhitespace(color[i]))
            return (0);
        i++;
    }
    return (1);
}

void validate_rgb(char **color)
{
    int i;

    i = 0;
    if(!color || !color[i])
    {
        ft_printf("\nRGB ERROR 1\n");
        exit(EXIT_FAILURE); 
        return ;
    }
    while (color[i] && ft_confirm_line_rgb(color[i]) == 1)
    {
        if (i >= 3)
        {
            ft_printf("\nRGB ERROR 2\n");
            exit(EXIT_FAILURE);
            return ;
        }
        i++;
    }
    if (i != 3)
    {
        ft_printf("\nRGB ERROR 2\n");
        exit(EXIT_FAILURE);
        return ;
    }
}
void get_rgb_fr_str(char *line, t_data *cub, int id)
{
    char **color;
    int i;

    color = ft_split(line, ',');
    i = 0;
    validate_rgb(color);
    while (color[i])
    {
        if (id == CEILING)
            cub->cl_rgb[i] = ft_atoi(color[i]);
        if (id == FLOOR)
            cub->fl_rgb[i] = ft_atoi(color[i]);
        i++;
    }
    //free splited
}

void check_color_range(t_data *cub)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (cub->fl_rgb[i] < 0 || cub->fl_rgb[i] < 0)
        {
            ft_printf("RGB OUT OF RANGE\n");
            exit(EXIT_FAILURE);
        }
        if (cub->fl_rgb[i] > 255 || cub->fl_rgb[i] > 255)
        {
            ft_printf("RGB OUT OF RANGE\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}
void save_rgb(char *line, t_data *cub, int id)
{
    fill_counter(cub, id);
    get_rgb_fr_str(line, cub, id);
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

void    build_map(t_data *cub)
{
    int i;
    int j;
    
    cub->map = (int **)calloc(cub->map_h, sizeof(int *));
    if (!cub->map)
        exit(EXIT_FAILURE); //dar frees e erro de memoria  ft_error    
    i = -1;
    while (++i < cub->map_h)
    {
        cub->map[i] = (int *)calloc(cub->map_w, sizeof(int));
        if (!cub->map)
            exit(EXIT_FAILURE); //dar frees e erro de memoria ft_error
        j = -1;
        while (cub->line[(cub->l_start + i)][++j] != '\0')
           cub->map[i][j] = cub->line[(cub->l_start + i)][j];
    }
    map_space(cub);
}

void get_map_size(t_data *cub)
{
    ft_printf("[F] - MAP_SIZE\n");

    int i;
    int size;

    i = 0;
    while (cub->line[i])
    {
        if (cub->in_map == false)
        {
            has_reached_map(cub->line[i], cub);
            cub->l_start = i;
        }
        else if (cub->in_map == true)
        {
            //ft_printf("LINHAS %s\n", cub->line[i]);
            //if (is_empty_line(cub->line[i]));
  
            size = ft_strlen(cub->line[i]);
            if (cub->map_w < size)
                cub->map_w = size;
            cub->map_h++;
        }
        i++;
    }
    cub->map_h++; //for some reason it is not correct size
}

void read_mapfile(t_data *cub, char *filename)
{
    ft_printf("[F] - READ_MAPFILE\n");

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
            {
               ft_printf("[%i] FETCHING SCENICS: -> ", i);
               get_scenic_id(cub, i);
            }
            i++;
        }
    }
    //check other scenics here like if the xpm are correct
    check_color_range(cub);
}

void get_player_pos(t_data *cub)
{
	int i = 0;
	int j;
    
	while (i < cub->map_h)
	{
		j = 0;
		while (j < cub->map_w)
		{
			if (cub->map[i][j] == 78)
            {
                cub->init_x = j;
                cub->init_y = i;
                return ;
            }
			j++;
		}
		i++;
	}
    exit(EXIT_FAILURE);
}

void    map_space(t_data *cub)
{
    int i;

    i = 1;
    while (i < cub->map_h - 1)
    {
        if (cub->map[i][0] == '\n')
        {
            ft_printf("Invalid map\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void parser_first(t_data *cub)
{
    get_player_pos(cub);
    ft_printf("Nx = %i\n", cub->init_x);
    ft_printf("Ny = %i\n", cub->init_y);
    
      
    if (floodfill(cub, cub->init_x, cub->init_y, 48, 49) == 0)
    {
        ft_printf("\033[1;31mMAPA DEU MERDA\033[0m\n");
        exit(EXIT_FAILURE);
        return ;
    }
    ft_printf("\033[1;32m!MAPA OK!\033[0m\n");
    exit(EXIT_SUCCESS);
}

int floodfill(t_data *cub, int x, int y, int targ, int new)
{
    int current;
    int ret;

    ret = 0;

    if (x < 0 || x >= cub->map_w || y < 0 || y >= cub->map_h) 
        return 0;
    current = cub->map[y][x];
    if (current == 49)
        return 1;
    if (current != targ && current != 78)
        return 0;

    cub->map[y][x] = new;

    ret += floodfill(cub, x - 1, y, targ, new);
    ret += floodfill(cub, x + 1, y, targ, new);
    ret += floodfill(cub, x, y - 1, targ, new);
    ret += floodfill(cub, x, y + 1, targ, new);

    if (ret == 4)
        return 1;
    return 0;
}
