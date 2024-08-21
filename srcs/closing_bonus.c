/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:04:45 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 16:57:15 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	close_win_free(t_data *cub);

int	close_win_free(t_data *cub)
{
	general_free(cub);
	if (cub->win_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->img)
		mlx_destroy_image(cub->mlx_ptr, cub->img);
	if (cub->mlx_ptr)
		mlx_destroy_display(cub->mlx_ptr);
	if (cub->mlx_ptr)
		free(cub->mlx_ptr);
	ft_printf("\n-- Display Cleared --\n");
	exit(EXIT_SUCCESS);
}
