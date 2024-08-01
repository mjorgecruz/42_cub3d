/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:10:19 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/04 12:39:46 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(int c)
{
	return (c > 64 && c < 91);
}

static int	ft_islower(int c)
{
	return (c > 96 && c < 123);
}

int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
