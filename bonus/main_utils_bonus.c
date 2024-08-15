/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:57:21 by masoares          #+#    #+#             */
/*   Updated: 2024/08/15 21:12:03 by masoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

bool	ft_cubfile(char *str);
void	check_user_input(int ac, char *av, t_data *cub);
int		ft_strcmp(char *s1, char *s2);

void check_user_input(int ac, char *av, t_data *cub)
{
	if (ac != 2)
		ft_error(INPUTERR, cub);
	else if (!ft_cubfile(av))
		ft_error(MAPNAME, cub);
}

bool ft_cubfile(char *str)
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
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}