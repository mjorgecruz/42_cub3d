/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:23:03 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/07/30 12:23:12 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void read_mapfile(t_data *cub, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY, 0);
    is_fd_invalid(fd, cub);
    char *lol;
    lol = get_next_line(fd);
    ft_printf("%s", lol);
    free(lol);
    close (fd);
}

/*
while the file is open we go thru each line, 
first we identify each line direction "NO SO WE EA" and 
get the path for the same and use this function to fill it:  
int texture_id(char *str);          to get the direction id
we should also get the path and pass it along to the next function:
int validate_textures(t_data *data, char *path, int direction);
(in a loop until all the 4 textures are filled (can we repeat paths?) 
    // Using get next line
    //while file is open check all the other steps and
    // make functions for the get textures and colors
    //amd fill the map
    */