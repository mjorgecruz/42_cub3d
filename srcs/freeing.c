/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:04 by masoares          #+#    #+#             */
/*   Updated: 2024/07/29 14:45:55 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	general_free(t_data *cub)
{
	int	k;

	k = 0;
	while (k < cub->map_h)
	{
		free(cub->map[k]);
		k++;
	}
	free(cub->map);
	printf("\n -- GENERAL FREED -- \n");
}