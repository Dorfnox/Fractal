/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 16:05:32 by bpierce           #+#    #+#             */
/*   Updated: 2017/06/14 23:43:19 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (n == 0)
		return (1);
	if (s1_len != s2_len)
		return (0);
	if (s1_len == 0)
		return (1);
	if (ft_strncmp(s1, s2, n) == 0)
		return (1);
	return (0);
}
