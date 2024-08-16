/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 13:23:36 by masoares          #+#    #+#             */
/*   Updated: 2024/08/16 14:09:28 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

int	handle_mouse_move(int x, int y, t_data *cub)
{
    if (x > 0 && x < WIN_W && y > 0 && y < WIN_H)
    {
	    cub->player->p_ang += (x - cub->player->prev_x) * (720.0 * DG_RAD)/ (double) (WIN_W);
        cub->player->prev_x = x;
    }
    render_bonus(cub);
	return (0);
}
