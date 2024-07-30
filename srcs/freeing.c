/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:07:04 by masoares          #+#    #+#             */
/*   Updated: 2024/07/30 12:07:39 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	// free(cub->south);
	// free(cub->north);
	// free(cub->west);
	// free(cub->east);
	ft_printf("\n -- GENERAL FREED -- \n");
}