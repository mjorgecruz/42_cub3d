/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileread_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:25:06 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/01 10:03:18 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void is_fd_invalid(int fd, t_data *cub);
int ft_iswhitespace(int c);
int jump_whitepaces(char *line);

void is_fd_invalid(int fd, t_data *cub)
{
    if (fd < 0)
        ft_error(CANTOPEN, cub);
    return ;
}

int ft_iswhitespace(int c)
{
    return (c == 32 || (c >= 9 && c <= 13));
}

int jump_whitepaces(char *line)
{
    int i;

    i = 0;
    while (ft_iswhitespace(line[i]))
        i++;
    return (i);
}