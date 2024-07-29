/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:53:30 by masoares          #+#    #+#             */
/*   Updated: 2024/07/29 14:45:45 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	key_detect(int key, t_data *cub)
{
	if (key == XK_Escape)
		close_win_free(cub);
	(void) cub;
	(void) key;
	printf("key %x \n", key);
	return (1);
}