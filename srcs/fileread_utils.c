/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:25:06 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/07/30 11:59:27 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void is_fd_invalid(int fd, t_data *cub)
{
    if (fd < 0)
        ft_error(CANTOPEN, cub);
    return ;
}

int get_texture_id(char *str)
{
    if (ft_strncmp(str, "NO", 2))
        return (NORTH);
    if (ft_strncmp(str, "SO", 2))
        return (SOUTH);
    if (ft_strncmp(str, "WE", 2))
        return (WEST);
    if (ft_strncmp(str, "EA", 2))
        return (EAST);
    return(-1);
}

// char *copy_txtr_path(t_data *cub, int id)
// {
//     if (id == NORTH)
//     cub->north = ;
//     if (id == SOUTH)
//     cub->south = ;
//     if (id == WEST)
//     cub->south = ;
//     if (id == EAST)
//     cub->east = ;
// }
