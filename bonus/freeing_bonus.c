/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:04 by masoares          #+#    #+#             */
/*   Updated: 2024/08/15 21:11:47 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	if (cub->player)
	{	
		if (cub->player->cam)
			free(cub->player->cam);
		if(cub->player->pov)
			free(cub->player->pov);
		free(cub->player);
	}
	if (cub->texEast.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texEast.img);
	if (cub->texNorth.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texNorth.img);
	if (cub->texSouth.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texSouth.img);
	if (cub->texWest.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texWest.img);
}
void	general_free(t_data *cub)
{
	ft_free_array(cub, cub->map);
	ft_free_array(cub, cub->map_cpy);
	ft_free_struct_a(cub);
	//free(cub);
	ft_printf("\n -- GENERAL FREED -- \n");
}