/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 10:54:20 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/24 16:34:57 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_map_size(t_data *cub);
void	build_map(t_data *cub);
void	make_map_copy(t_data *cub);

void	get_map_size(t_data *cub)
{
	int	i;
	int	size;

	i = -1;
	cub->in_map = false;
	while (cub->line[++i])
	{
		if (cub->in_map == false)
		{
			has_reached_map(cub->line[i], cub);
			cub->l_start = i;
		}
		if (cub->in_map == true)
		{
			size = ft_strlen(cub->line[i]);
			if (cub->map_w < size)
				cub->map_w = size;
			cub->map_h++;
		}
	}
	cub->map_w++;
}

void	build_map(t_data *cub)
{
	int	i;
	int	j;

	cub->map = (int **)ft_calloc(cub->map_h, sizeof(int *));
	if (!cub->map)
		ft_error(MEMERR, cub);
	i = -1;
	while (++i < cub->map_h)
	{
		cub->map[i] = (int *)ft_calloc(cub->map_w, sizeof(int));
		if (!cub->map)
			ft_error(MEMERR, cub);
		j = -1;
		while (cub->line[(cub->l_start + i)][++j] != '\0')
			cub->map[i][j] = cub->line[(cub->l_start + i)][j];
	}
	map_space(cub);
}

void	make_map_copy(t_data *cub)
{
	int	i;
	int	j;

	cub->map_cpy = (int **)ft_calloc(cub->map_h, sizeof(int *));
	if (!cub->map_cpy)
		ft_error(MEMERR, cub);
	i = -1;
	while (++i < cub->map_h)
	{
		cub->map_cpy[i] = (int *)ft_calloc(cub->map_w, sizeof(int));
		if (!cub->map_cpy)
			ft_error(MEMERR, cub);
		j = -1;
		while (++j < cub->map_w)
			cub->map_cpy[i][j] = cub->map[i][j];
	}
}
