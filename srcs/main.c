/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/07/30 12:02:34 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	window_updater(t_data *cub)
{
	mlx_destroy_image(cub->mlx_ptr, cub->img);
	cub->img = mlx_new_image(cub->mlx_ptr, cub->img_w, cub->img_h);
}

int	main(int argc, char **argv)
{
	t_data	cub;
	ft_printf("Piroca 0\n");

	check_user_input(argc, argv[1], &cub);
	/*testing GNL */
	ft_printf("Piroca 1\n");
	read_mapfile(&cub, argv[1]);
	ft_printf("Piroca 2\n");
	/*coment this up here if you need */	
	init_fields(&cub);
	minimaper(&cub);
	run_window(&cub);
}
