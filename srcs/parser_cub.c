/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:30:36 by masoares          #+#    #+#             */
/*   Updated: 2024/07/30 11:40:36 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void read_mapfile(t_data *cub, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY, 0);
    is_fd_invalid(fd, cub);
    ft_printf("%S", get_next_line(fd));
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