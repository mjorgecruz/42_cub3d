/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:17:26 by masoares          #+#    #+#             */
/*   Updated: 2024/08/21 11:02:24 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d_bonus.h"

void	animate_door_opening(t_data *cub, int door_num);
void	update_door_position(t_door *door);
void	update_fire(t_data *cub);

void	animate_door_opening(t_data *cub, int door_num)
{
	if (cub->doors[door_num].status == 0)
		cub->doors[door_num].status = 1;
	else if (cub->doors[door_num].status == 2)
	{
		cub->doors[door_num].status = 3;
	}
	cub->doors[door_num].last_time = get_time();
	return ;
}

void	update_door_position(t_door *door)
{
	double	ongoing_time;

	door->current_time = get_time();
	ongoing_time = door->current_time - door->last_time;
	door->last_time = door->current_time;
	if (door->status == 1)
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
	}
}

void	update_fire(t_data *cub)
{
	double	ongoing_time;
	int		i;

	i = 0;
	ongoing_time = get_time() - cub->fire_last_time;
	if (ongoing_time < 50)
		cub->fire_num = 0;
	else if (ongoing_time < 100)
		cub->fire_num = 1;
	else if (ongoing_time < 150)
		cub->fire_num = 2;
	else
	{
		cub->fire_num = 0;
		cub->fire_last_time = get_time();
	}
	if (cub->fires)
	{
		while (cub->fires[i].pos_x != -1)
		{
			cub->fires[i].drawn = 0;
			i++;
		}
	}
	return ;
}
