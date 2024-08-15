/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:18 by masoares          #+#    #+#             */
/*   Updated: 2024/08/15 11:47:52 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"


void    ft_perror(char *msg)
{
    int size;

    size = ft_strlen(msg);
    write(STDERR_FILENO, msg, size);
    // exit(EXIT_FAILURE);
}

void ft_error(int n, t_data *cub)
{
    ft_perror("\033[31mERROR\033[0m\n");
    if  (n == INPUTERR)
        ft_perror("\033[31mInvalid input\033[0m\nUSE:[./cub3d mapname.cub]\n");
    else if  (n == MAPNAME)
        ft_perror("\033[31mIncorrect map name\033[0m\nUSE:[./cub3d mapname.cub]\n");
    else if  (n == CANTOPEN)
        ft_perror("\033[31mCouldn't open file\033[0m\n");
    else if  (n == PATHERR)
        ft_perror("\033[31mCouldn't reach texture path\033[0m\n");
    ft_perror("UNSPECIFIED ERROR\n");
    general_free(cub);
    exit(EXIT_FAILURE);
}

//still needs to open texture