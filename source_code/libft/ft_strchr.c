/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdugot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:26:49 by mdugot            #+#    #+#             */
/*   Updated: 2015/11/25 12:28:15 by mdugot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char *temp;

	temp = (char*)s;
	while (*temp != '\0')
	{
		if (*temp == (char)c)
			return (temp);
		temp++;
	}
	if (c == '\0')
		return (temp);
	else
		return (NULL);
}
