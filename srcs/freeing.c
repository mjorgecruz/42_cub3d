/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:04 by masoares          #+#    #+#             */
/*   Updated: 2024/08/14 16:04:29 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    ft_free_split(char **array)
{
    int i;

    i = 0;
    if (array != NULL)
    {
        while (array[i] != NULL)
            free(array[i++]);
    }
    free(array);
}
void ft_free_array(t_data *cub, int **array)
{
    int i;
    
    if(!array)
        return ;
    i = cub->map_h;
    while (--i >= 0)
    {
        free(array[i]);
    }
    free(array);
}

void	ft_free_struct_a(t_data *cub)
{
	// int i;

	// i = -1;
	if	(cub->north)
		free(cub->north);
	if (cub->south)
		free(cub->south);
	if (cub->west)
		free(cub->west);
	if (cub->east)
		free(cub->east);
	while (--cub->lc >= 0)
		free(cub->line[cub->lc]);
	free(cub->line);
}
void	general_free(t_data *cub)
{
	ft_free_array(cub, cub->map);
	ft_free_array(cub, cub->map_cpy);
	ft_free_struct_a(cub);
	//free(cub);
	//free t_player
	ft_printf("\n -- GENERAL FREED -- \n");
}