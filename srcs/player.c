/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:29:59 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/16 16:30:18 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_player	*init_player(t_data *cub);

t_player	*init_player(t_data *cub)
{
	t_player	*player;

	player = (t_player *) malloc(sizeof(t_player) * 1);
	if (player == NULL)
		ft_error(MEMERR, cub);
	player->pov = (t_pov *) malloc(sizeof(t_pov) * 1);
	init_orientation(player, cub->player_init_ori);
	init_camera(player, cub);
	return (player);
}
