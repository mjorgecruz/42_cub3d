/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_bonus6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:21:02 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 12:37:08 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ctrl_trans_helper_neg(t_data *cub)
{
	cub->player->posy = cub->player->posy - sin(cub->player->p_ang) / 20;
	cub->player->posx = cub->player->posx - cos(cub->player->p_ang) / 20;
}

void	math_helper_door1(t_data *cub)
{
	cub->player->posx = cub->player->posx - sin(cub->player->p_ang) / 20;
}

void	math_helper_door2(t_data *cub)
{
	cub->player->posy = cub->player->posy + cos(cub->player->p_ang) / 20;
}

void	math_helper_door3(t_data *cub)
{
	cub->player->posy = cub->player->posy - cos(cub->player->p_ang) / 20;
	cub->player->posx = cub->player->posx + sin(cub->player->p_ang) / 20;
}

void	math_door4_helper(t_data *cub)
{
	cub->player->posy = cub->player->posy - cos(cub->player->p_ang) / 20;
}
