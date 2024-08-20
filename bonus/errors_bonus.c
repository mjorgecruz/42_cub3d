/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:31:18 by masoares          #+#    #+#             */
/*   Updated: 2024/08/20 13:56:11 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void		ft_perror(char *msg);
void		ft_error_plus(int n, t_data *cub);
void		ft_error(int n, t_data *cub);

void	ft_perror(char *msg)
{
	int	size;

	size = ft_strlen(msg);
	write(STDERR_FILENO, msg, size);
}

void	ft_error_plus(int n, t_data *cub)
{
	if (n == MLX)
		ft_perror("\033[31mMLX ERROR.\033[0m\n");
	else if (n == WINDOW)
		ft_perror("\033[31mWINDOW ERROR.\033[0m\n");
	else if (n == CUBIMG)
		ft_perror("\033[31mCUBIMG ERROR.\033[0m\n");
	else if (n == MISSTEXT)
		ft_perror("\033[31m Invalid Texture.\033[0m\n");
	else if (n == CAMERA)
		ft_perror("\033[31mCAMERA ERROR.\033[0m\n");
	else if (n == SCENIC)
		ft_perror("\033[31mInvalid scenics\033[0m\n");
	else
		ft_perror("UNSPECIFIED ERROR\n");
	general_free(cub);
	exit(EXIT_FAILURE);
}

void	ft_error(int n, t_data *cub)
{
	ft_perror("\033[31mERROR\033[0m\n");
	if (n == INPUTERR)
		ft_perror("\033[31mInvalid input\033[0m\nUSE:[./cub3d map.cub]\n");
	else if (n == MAPNAME)
		ft_perror("\033[31mInvalid map name\033[0m\nUSE:[./cub3d map.cub]\n");
	else if (n == CANTOPEN)
		ft_perror("\033[31mCouldn't open file.\033[0m\n");
	else if (n == MISSTEXT)
		ft_perror("\033[31m Invalid Texture.\033[0m\n");
	else if (n == PLAYER)
		ft_perror("\033[31mPlayr Position ERROR.\033[0m\n");
	else if (n == IVALIDMAP)
		ft_perror("\033[31mInvalid Map.\033[0m\n");
	else if (n == RGBS)
		ft_perror("\033[31mInvalid RGB Format.\033[0m\n");
	else if (n == MEMERR)
		ft_perror("\033[31mMem Alloc Error.\033[0m\n");
	else
		ft_error_plus(n, cub);
	general_free(cub);
	exit(EXIT_FAILURE);
}
