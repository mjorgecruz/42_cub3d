/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 13:23:36 by masoares          #+#    #+#             */
/*   Updated: 2024/08/17 14:41:19 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

int	handle_mouse_move(int x, int y, t_data *cub)
{
    if (x < 30)
        x = WIN_W - 30;
    else if (x > WIN_W - 30)
        x = 30;
    // if (x > 0 && x < WIN_W && y > 0 && y < WIN_H)
    // {
	//     cub->player->p_ang += (x - cub->player->prev_x) * (415.0 * DG_RAD)/ (double) (WIN_W);
    //     cub->player->prev_x = x;
    // }
    mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, x, y);
    if (x == cub->player->prev_x)
        return (0);
    else
        cub->player->p_ang += (x - cub->player->prev_x) * DG_RAD;
    cub->player->prev_x = x;
    render_bonus(cub);
	return (0);

    //falta introduzir velocidade de rotacao e velocidade de traslacao
}
