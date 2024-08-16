/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:57:21 by masoares          #+#    #+#             */
/*   Updated: 2024/08/16 14:23:35 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	ft_cubfile(char *str);
void	check_user_input(int ac, char *av, t_data *cub);
int		ft_strcmp(char *s1, char *s2);

void	check_user_input(int ac, char *av, t_data *cub)
{
	if (ac != 2)
		ft_error(INPUTERR, cub);
	else if (!ft_cubfile(av))
		ft_error(MAPNAME, cub);
}

bool	ft_cubfile(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = ft_strlen(str);
	while (i >= 0 && str[i] != '.')
		i--;
	if (i == 0)
		return (false);
	if (ft_strcmp("cub", str + i + 1) == 0)
		return (true);
	return (false);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	tex_preparer(t_data *cub)
{
	cub->texEast.data = NULL;
	cub->texNorth.data = NULL;
	cub->texSouth.data = NULL;
	cub->texWest.data = NULL;
	cub->texEast.img = NULL;
	cub->texNorth.img = NULL;
	cub->texSouth.img = NULL;
	cub->texWest.img = NULL;
	cub->door.data = NULL;
	cub->door.img = NULL;
	cub->north = NULL;
	cub->south = NULL;
	cub->east = NULL;
	cub->west = NULL;
	cub->map = NULL;
	cub->map_cpy = NULL;
	cub->player = NULL;
	cub->doors = NULL;
}

void	field_filler(t_data *cub)
{
	tex_preparer(cub);
	cub.map_h = 0;
	cub.map_w = 0;
	cub.count[0] = 0;
	cub.count[1] = 0;
	cub.count[2] = 0;
	cub.count[3] = 0;
	cub.count[4] = 0;
	cub.count[5] = 0;
	cub.l_start = 0;
	cub.init_x = -1;
	cub.init_y = -1;
	cub.lc = 0;
	cub.line = NULL;
	cub.in_map = false;
}
