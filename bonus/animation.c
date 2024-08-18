/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:17:26 by masoares          #+#    #+#             */
/*   Updated: 2024/08/18 19:28:03 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void 	animate_door_opening(t_data *cub, int door_num)
{
    if (cub->doors[door_num].status == 0)
        cub->doors[door_num].status = 1;
    else if (cub->doors[door_num].status == 2)
    {
        cub->doors[door_num].status = 3;
    }
	cub->doors[door_num].last_time = get_time();
	return;
}
void update_door_position(t_door *door)
{
	double	current_time;
	double	ongoing_time;
	
	current_time = get_time();
	ongoing_time = current_time - door->last_time;
	door->last_time = current_time;
	if(door->status == 1)
	{
		door->position += door->speed * ongoing_time;
        if (door->position >= 1.0)
        {
            door->position = 1.0;
            door->status = 2;
            door->open = true;
        }
	}
	else if (door->status == 3)
    {
        door->position -= door->speed * ongoing_time;
        if (door->position <= 0.0)
        {
            door->position = 0.0;
            door->status = 0;
            door->open = false;
        }
        printf(" position %f  %d\n", door->position, door->open);
    }
}
