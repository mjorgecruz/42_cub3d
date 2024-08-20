/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:17:34 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/20 14:32:32 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	check_scenics_count(t_data *cub);
void	check_scenics(t_data *cub);
void	check_duplicates(t_data *cub, int id);
void	fill_counter(t_data *cub, int id);
void	get_scenic_id(t_data *cub, int i);

void	check_scenics_count(t_data *cub)
{
	int	i;

	i = -1;
	while (++i <= 5)
	{
		if (cub->count[i] == 0)
			ft_error(SCENIC, cub);
	}
}

void	check_scenics(t_data *cub)
{
	check_scenics_count(cub);
	check_xpm_format(cub);
	check_xpm_exist(cub);
}

void	check_duplicates(t_data *cub, int id)
{
	if (cub->count[id] == 1)
	{
		ft_error(SCENIC, cub);
	}
}

void	fill_counter(t_data *cub, int id)
{
	check_duplicates(cub, id);
	cub->count[id] = 1;
}

void	get_scenic_id(t_data *cub, int i)
{
	char	*p;

	p = cub->line[i];
	if (is_empty_line(p) == true)
		return ;
	else if (ft_strncmp((p + jump_whitepaces(p)), "NO ", 3) == 0)
		save_path(((p + jump_whitepaces(p)) + 3), cub, NORTH);
	else if (ft_strncmp((p + jump_whitepaces(p)), "SO ", 3) == 0)
		save_path(((p + jump_whitepaces(p)) + 3), cub, SOUTH);
	else if (ft_strncmp((p + jump_whitepaces(p)), "WE ", 3) == 0)
		save_path(((p + jump_whitepaces(p)) + 3), cub, WEST);
	else if (ft_strncmp((p + jump_whitepaces(p)), "EA ", 3) == 0)
		save_path(((p + jump_whitepaces(p)) + 3), cub, EAST);
	else if (ft_strncmp((p + jump_whitepaces(p)), "F ", 2) == 0)
		save_rgb((p + jump_whitepaces(p) + 2), cub, FLOOR);
	else if (ft_strncmp((p + jump_whitepaces(p)), "C ", 2) == 0)
		save_rgb(((p + jump_whitepaces(p)) + 2), cub, CEILING);
	else
		ft_error(SCENIC, cub);
}
