/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:18 by masoares          #+#    #+#             */
/*   Updated: 2024/07/29 22:44:02 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_error(int n, t_data *cub)
{
    if  (n == INPUTERR)
        printf("ERROR 001\nInvalid input\nUSE:[./cub3d mapname.cub]\n");
    else if  (n == MAPNAME)
        printf("ERROR 002\nIncorrect map name\nUSE:[./cub3d mapname.cub]\n");
    else if  (n == CANTOPEN)
        printf("ERROR\nCouldn't open file\n");
    else if  (n == PATHERR)
        printf("ERROR\nCouldn't reach texture path\n");
    close_win_free(cub);
    exit(EXIT_FAILURE);
}


