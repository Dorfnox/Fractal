/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 14:57:49 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 10:11:44 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	*new_background_image(t_fractol *f, int w, int h)
{
	int		x;
	int		y;
	t_image	*background;

	background = new_image(f, w, h);
	y = -1;
	while (++y < 40)
	{
		x = -1;
		while (++x < W)
		{
			if (x < (W * 1 / 3))
				set_image_pixel(background, x, y, 0xFFA07A);
			else if (x < (W * 2 / 3))
				set_image_pixel(background, x, y, 0x98FB98);
			else
				set_image_pixel(background, x, y, 0xB0E0E6);
		}
	}
	return (background);
}

void		*new_bar_image(t_fractol *f, int w, int h, unsigned int col)
{
	int		x;
	int		y;
	void	*bar;

	bar = new_image(f, w, h);
	y = -1;
	while (++y < 40)
	{
		x = -1;
		while (++x < w)
			set_image_pixel(bar, x, y, col);
	}
	return (bar);
}

t_col_bars	*get_colour_bars(t_fractol *f)
{
	t_col_bars	*c;
	int			x;
	int			y;

	x = -1;
	y = -1;
	c = (t_col_bars *)malloc(sizeof(t_col_bars));
	c->b_ground = new_background_image(f, W, 40);
	c->r_bar = new_bar_image(f, ((W / 3.0) * f->r / 255), 40, 0xFF6347);
	c->g_bar = new_bar_image(f, ((W / 3) * f->g / 255), 40, 0x228B22);
	c->b_bar = new_bar_image(f, ((W / 3) * f->b / 255), 40, 0x1E90FF);
	return (c);
}

void		change_colour_value(t_fractol *f, char rgb, int s, int x)
{
	if (rgb == 'r')
	{
		f->r = (int)(((double)x / ((double)W / 3.0)) * 255.0);
		mlx_destroy_image(f->mlx, f->col_bars->r_bar->img);
		f->col_bars->r_bar = new_bar_image(f, x, 40, 0xFF6347);
		f->col_tab = !s ? get_col_tab(f, f->col_tab) :
			get_col_tab_smooth(f, f->col_tab);
	}
	else if (rgb == 'g')
	{
		f->g = (int)(((double)x / ((double)W / 3.0)) * 255.0) + 1;
		mlx_destroy_image(f->mlx, f->col_bars->g_bar->img);
		f->col_bars->g_bar = new_bar_image(f, x - (W / 3), 40, 0x228B22);
		f->col_tab = !s ? get_col_tab(f, f->col_tab) :
			get_col_tab_smooth(f, f->col_tab);
	}
	else if (rgb == 'b')
	{
		f->b = (int)(((double)x / ((double)W / 3.0)) * 255.0) + 2;
		mlx_destroy_image(f->mlx, f->col_bars->b_bar->img);
		f->col_bars->b_bar = new_bar_image(f, x - (W * 2 / 3), 40, 0x1E90FF);
		f->col_tab = !s ? get_col_tab(f, f->col_tab) :
			get_col_tab_smooth(f, f->col_tab);
	}
}
