/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:23:03 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/20 14:32:22 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	save_path(char *line, t_data *cub, int id);
bool	has_reached_map(char *line, t_data *cub);
void	read_mapfile(t_data *cub, char *filename);
void	read_lines(t_data *cub);
void	check_xpm_exist(t_data *cub);

void	save_path(char *line, t_data *cub, int id)
{
	int	i;

	if (!line)
		return ;
	i = jump_whitepaces(line);
	fill_counter(cub, id);
	if (id == NORTH)
	{
		cub->north = clear_path(&line[i]);
	}
	else if (id == SOUTH)
	{
		cub->south = clear_path(&line[i]);
	}
	else if (id == WEST)
	{
		cub->west = clear_path(&line[i]);
	}
	else if (id == EAST)
	{
		cub->east = clear_path(&line[i]);
	}
}

bool	has_reached_map(char *line, t_data *cub)
{
	int	i;

	i = 0;
	if (is_empty_line(line))
		return (false);
	else if (!line[i] || line[i] == '\n')
		return (false);
	else if (cub->in_map == false)
	{
		while (line[i] == '1' || line[i] == '0' || line[i] == ' ')
			i++;
		if (line[i] == '\0' || line[i] == '\n')
			cub->in_map = true;
		return (true);
	}
	return (false);
}

void	read_mapfile(t_data *cub, char *filename)
{
	int		fd;
	char	*temp;
	char	*temp2;
	char	*join;

	fd = open(filename, O_RDONLY, 0);
	is_fd_invalid(fd, cub);
	join = ft_strdup("");
	temp = get_next_line(fd);
	while (temp)
	{
		cub->lc++;
		temp2 = ft_strjoin(join, "*");
		free(join);
		join = ft_strjoin(temp2, temp);
		free(temp);
		free(temp2);
		temp = get_next_line(fd);
	}
	close(fd);
	cub->line = ft_split(join, '*');
	free(join);
}

void	read_lines(t_data *cub)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	cub->in_map = false;
	while (cub->line[i] != NULL)
	{
		length = ft_strlen(cub->line[i]);
		if (cub->line[i][length -1] == '\n')
			cub->line[i][length -1] = 0;
		if (is_empty_line(cub->line[i]))
			i++;
		else
		{
			if (cub->in_map == false)
				has_reached_map(cub->line[i], cub);
			if (cub->in_map == false)
				get_scenic_id(cub, i);
			i++;
		}
	}
	check_scenics(cub);
	check_color_range(cub);
}

void	check_xpm_exist(t_data *cub)
{
	int	fd;

	fd = open(cub->north, O_RDONLY, 0);
	if (fd < 0)
		ft_error(MISSTEXT, cub);
	close(fd);
	fd = open(cub->south, O_RDONLY, 0);
	if (fd < 0)
		ft_error(MISSTEXT, cub);
	close(fd);
	fd = open(cub->east, O_RDONLY, 0);
	if (fd < 0)
		ft_error(MISSTEXT, cub);
	close(fd);
	fd = open(cub->west, O_RDONLY, 0);
	if (fd < 0)
		ft_error(MISSTEXT, cub);
	close(fd);
}
