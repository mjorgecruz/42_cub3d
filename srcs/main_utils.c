/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masoares <masoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:57:21 by masoares          #+#    #+#             */
/*   Updated: 2024/07/29 13:34:53 by masoares         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	check_user_input(int ac, char *s)
{
	return ;
	
	if (ac != 2 || open(s, O_RDONLY, 0) < 0)
	{
		printf("Correct use: ./cub3d <filename>\n");
		exit(EXIT_SUCCESS);
	}
}