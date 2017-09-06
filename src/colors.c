/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 23:20:56 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/19 15:37:58 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			*int_table(int size)
{
	int		*new;

	if (!(new = (int *)malloc(sizeof(int) * size)))
		return (NULL);
	new[0] = 0x0;
	return (new);
}

int			*get_col_tab_offset(t_fractol *f, int *old_tab)
{
	short			i;
	double			rgb;
	double			new_rgb;

	if (!(old_tab))
		if (!(old_tab = int_table(f->n_colours)))
			return (NULL);
	rgb = (double)(f->r + f->g + f->b) / 3.0;
	i = -1;
	while (++i < (short)f->n_colours)
	{
		new_rgb = rgb + 2 * (fmod(rand(), 256.0)) * 0.23 - 0.23;
		old_tab[i] = ft_rgb_to_hex(
				f->r * (rgb / new_rgb),
				f->g * (rgb / new_rgb),
				f->b * (rgb / new_rgb));
	}
	return (old_tab);
}

int			*get_col_tab(t_fractol *f, int *old_tab)
{
	short			i;
	t_colours		rgb;

	if (!old_tab)
		if (!(old_tab = int_table(f->n_colours)))
			return (NULL);
	rgb.r = fmod(rand(), 256.0);
	rgb.g = fmod(rand(), 256.0);
	rgb.b = fmod(rand(), 256.0);
	i = -1;
	while (++i < (short)f->n_colours)
	{
		old_tab[i] = ft_rgb_to_hex(
				f->r + (((rgb.r - f->r) / (double)f->n_colours) * i),
				f->g + (((rgb.g - f->g) / (double)f->n_colours) * i),
				f->b + (((rgb.b - f->b) / (double)f->n_colours) * i));
	}
	return (old_tab);
}

int			*get_col_tab_smooth(t_fractol *f, int *old_tab)
{
	short			i;
	double			new_rgb;

	if (!old_tab)
		if (!(old_tab = int_table(f->n_colours)))
			return (NULL);
	new_rgb = 0;
	i = 0;
	while (i < (short)f->n_colours)
	{
		old_tab[i] = ft_rgb_to_hex(
				f->r * (new_rgb / 256),
				f->g * (new_rgb / 256),
				f->b * (new_rgb / 256));
		new_rgb = (256.0 / (double)f->n_colours) * (++i);
	}
	return (old_tab);
}

int			*get_col_tab_random(t_fractol *f, int *old_tab)
{
	short			i;

	if (!old_tab)
		if (!(old_tab = int_table(f->n_colours)))
			return (NULL);
	i = -1;
	while (++i < (short)f->n_colours)
	{
		old_tab[i] = ft_rgb_to_hex(
				fmod(rand(), 256),
				fmod(rand(), 256),
				fmod(rand(), 256));
	}
	return (old_tab);
}
