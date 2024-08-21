/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:04 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 11:51:45 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

void		ft_free_split(char **array);
void		general_free(t_data *cub);
void		ft_free_array(t_data *cub, int **array);
void		free_mlx_checker(t_data *cub);

void	ft_free_split(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
			free(array[i++]);
	}
	free(array);
}

void	ft_free_array(t_data *cub, int **array)
{
	int	i;

	if (!array)
		return ;
	i = cub->map_h;
	while (--i >= 0)
		free(array[i]);
	free(array);
}

void	free_mlx_checker(t_data *cub)
{
	if (cub->texeast.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texeast.img);
	if (cub->texnorth.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texnorth.img);
	if (cub->texsouth.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texsouth.img);
	if (cub->texwest.img)
		mlx_destroy_image(cub->mlx_ptr, cub->texwest.img);
	if (cub->fire1.img)
		mlx_destroy_image(cub->mlx_ptr, cub->fire1.img);
	if (cub->fire2.img)
		mlx_destroy_image(cub->mlx_ptr, cub->fire2.img);
	if (cub->fire3.img)
		mlx_destroy_image(cub->mlx_ptr, cub->fire3.img);
	if (cub->door.img)
		mlx_destroy_image(cub->mlx_ptr, cub->door.img);
}

void	ft_free_struct_a(t_data *cub)
{
	if (cub->north)
		free(cub->north);
	if (cub->south)
		free(cub->south);
	if (cub->west)
		free(cub->west);
	if (cub->east)
		free(cub->east);
	ft_free_split(cub->line);
	if (cub->player)
	{
		if (cub->player->cam)
			free(cub->player->cam);
		if (cub->player->pov)
			free(cub->player->pov);
		free(cub->player);
	}
	free_mlx_checker(cub);
	if (cub->fires)
		free(cub->fires);
	if (cub->doors)
		free(cub->doors);
}

void	general_free(t_data *cub)
{
	ft_free_array(cub, cub->map);
	ft_free_array(cub, cub->map_cpy);
	ft_free_struct_a(cub);
	ft_printf("\n -- GENERAL FREED -- \n");
}
