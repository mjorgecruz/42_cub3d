/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:04 by masoares          #+#    #+#             */
/*   Updated: 2024/08/19 12:05:24 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}

void	general_free(t_data *cub)
{
	ft_free_array(cub, cub->map);
	ft_free_array(cub, cub->map_cpy);
	ft_free_struct_a(cub);
	ft_printf("\n -- GENERAL FREED -- \n");
}
