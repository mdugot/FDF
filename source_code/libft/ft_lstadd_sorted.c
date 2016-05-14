/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_sorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 16:12:13 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/29 17:58:43 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_sorted(t_list **alst, t_list *elem,\
		int (*cmp)(void *c1, void *c2))
{
	if ((alst == NULL || *alst == NULL) || elem == NULL || cmp == NULL)
		return ;
	if (cmp(elem->content, (*alst)->content) < 0)
		ft_lstadd_before(alst, *alst, elem);
	else if ((*alst)->next == NULL)
		(*alst)->next = elem;
	else
		ft_lstadd_sorted(&((*alst)->next), elem, cmp);
}
