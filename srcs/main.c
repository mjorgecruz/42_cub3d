/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/06/05 13:49:28 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

typedef struct s_info
{
	int		map_w;
	int		map_h;
	int		**map;
	void	*mlx;
	void	*mlx_win;
	int		img_w;
	int		img_h;
	void	*img;
	char	*addr;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
}		t_info;

t_info	*init_alloc(void)
{
	t_info	*cub;

	cub = malloc(sizeof(t_info));
	if (!cub)
		exit(EXIT_SUCCESS);
	return (cub);
}

static void	check_user_input(int ac, char *s)
{
	return ;
	
	if (ac != 2 || open(s, O_RDONLY, 0) < 0)
	{
		printf("Correct use: ./cub3d <filename>\n");
		exit(EXIT_SUCCESS);
	}
}

void	window_updater(t_info *cub)
{
	mlx_destroy_image(cub->mlx, cub->img);
	cub->img = mlx_new_image(cub->mlx, cub->img_w, cub->img_h);
	//draw);
}


void	general_free(t_info *cub)
{
	int	k;

	k = 0;
	while (k < cub->map_h)
	{
		free(cub->map[k]);
		k++;
	}
	free(cub->map);
	free(cub);
	printf("\n -- GENERAL FREED -- \n");
}

int	close_win_free(t_info *cub)
{
	mlx_destroy_window(cub->mlx, cub->mlx_win);
	mlx_destroy_image(cub->mlx, cub->img);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	printf("\n-- Display Cleared --\n");
	general_free(cub);
	exit(EXIT_SUCCESS);
}

void	init_fields(t_info *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "CUB3D");
	cub->img_w = 1920;
	cub->img_h = 1080;
	cub->img = mlx_new_image(cub->mlx, cub->img_w, cub->img_h);
	cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel,
			&cub->line_length, &cub->endian);
	cub->map_h = 0;
	cub->map_w = 0;
	cub->map = NULL;

}

int	key_detect(int key, t_info *cub)
{
	(void) cub;
	(void) key;
	printf("key %x \n", key);
	return (1);
}

void	run_window(t_info *cub)
{
	mlx_hook(cub->mlx_win, KeyPress, KeyPressMask, key_detect, cub);
	mlx_hook(cub->mlx_win, DestroyNotify, NoEventMask, close_win_free, cub);
}

int	main(int argc, char **argv)
{
	t_info	*cub;

	check_user_input(argc, argv[1]);
	cub = init_alloc();
	init_fields(cub);
	while (1)
	{
		run_window(cub);
	}
}
