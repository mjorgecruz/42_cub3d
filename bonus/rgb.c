/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:40:15 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/14 17:35:26 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int     ft_confirm_line_rgb(char *color);
void    get_rgb_fr_str(char *line, t_data *cub, int id);
void    check_color_range(t_data *cub);
void    save_rgb(char *line, t_data *cub, int id);
void    validate_rgb(char **color, t_data *cub);

int ft_confirm_line_rgb(char *color)
{
    int i;

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

void validate_rgb(char **color, t_data *cub)
{
    int i;
    int count;

    count = 0;
    i = -1;
    if(!color || !color[i + 1])
        ft_error(11, cub);
    while (color[++i])
    {
        if (!is_empty_line(color[i]))
        {
            if (ft_confirm_line_rgb(color[i]) == 1)
                count++;
        }
    }
    if (count != 3)
        ft_error(11, cub);
}

void get_rgb_fr_str(char *line, t_data *cub, int id)
{
    char **color;
    int i;
    int count;
    
    color = ft_split(line, ',');
    i = -1;
    count = 0;
    validate_rgb(color, cub);
    while (color[++i])
    {
        if (!is_empty_line(color[i]))
        {   
            if (id == CEILING)
                cub->cl_rgb[count++] = ft_atoi(color[i]);
            else if (id == FLOOR)
                cub->fl_rgb[count++] = ft_atoi(color[i]);
        }
    }
    ft_free_split(color);
    if (count > 3)
        ft_error(22, cub);
}

void check_color_range(t_data *cub)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (cub->fl_rgb[i] < 0 || cub->fl_rgb[i] > 255)
            ft_error(22, cub);
        else if (cub->cl_rgb[i] > 255 || cub->cl_rgb[i] < 0)
            ft_error(22, cub);
        i++;
    }
}

void save_rgb(char *line, t_data *cub, int id)
{
    fill_counter(cub, id);
    get_rgb_fr_str(line, cub, id);
}
