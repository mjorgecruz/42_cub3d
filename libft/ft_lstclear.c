/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luis-ffe <luis-ffe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:42:12 by luis-ffe          #+#    #+#             */
/*   Updated: 2023/10/08 18:47:35 by luis-ffe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*pnt;

	if (lst)
	{
		while (*lst)
		{
			pnt = (*lst)->next;
			ft_lstdelone(*lst, del);
			(*lst) = pnt;
		}
	}
}
