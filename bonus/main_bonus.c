/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 09:57:38 by luis-ffe          #+#    #+#             */
/*   Updated: 2024/08/21 15:23:19 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_data	cub;

	printf("\t  W or UP : move forward");
	printf("\tS or DOWN : move backward\n");
	printf("\t     A    : strafe left\t");
	printf("\t     D    : strafe right\n");
	printf("\t     <    : rotate left\t");
	printf("\t     >    : rotate right\n");
	field_filler(&cub);
	check_user_input(argc, argv[1], &cub);
	read_mapfile(&cub, argv[1]);
	read_lines(&cub);
	parser_first(&cub);
	init_fields_bonus(&cub);
	run_window_bonus(&cub);
	general_free(&cub);
	return (0);
}
