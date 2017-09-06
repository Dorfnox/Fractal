/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 13:58:54 by bpierce           #+#    #+#             */
/*   Updated: 2017/06/11 14:36:15 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*newdst;
	unsigned char	*newsrc;
	size_t			i;

	newdst = (unsigned char *)dst;
	newsrc = (unsigned char *)src;
	i = 0;
	while (i < n && newsrc[i] != (unsigned char)c)
	{
		newdst[i] = newsrc[i];
		i++;
	}
	if (i < n && newsrc[i] == (unsigned char)c)
	{
		newdst[i] = newsrc[i];
		return (&dst[i + 1]);
	}
	return (NULL);
}
