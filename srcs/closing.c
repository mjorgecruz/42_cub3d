/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:04:45 by masoares          #+#    #+#             */
/*   Updated: 2024/07/29 14:45:51 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	close_win_free(t_data *cub)
{
	mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	mlx_destroy_image(cub->mlx_ptr, cub->img);
	mlx_destroy_display(cub->mlx_ptr);
	free(cub->mlx_ptr);
	printf("\n-- Display Cleared --\n");
	general_free(cub);
	exit(EXIT_SUCCESS);
}