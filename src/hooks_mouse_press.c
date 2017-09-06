/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse_press.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 17:47:05 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/19 15:55:59 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mouse_press2(int button, int x, int y, t_fractol *f)
{
	if (button == MOUSEDOWN_K && y > (H - 40) && x > 0 && x < W / 3)
	{
		f->mousedown = MOUSEDOWNR_K;
		change_colour_value(f, 'r', 1, x);
		draw_stuff(f);
	}
	else if (button == MOUSEDOWN_K && y > (H - 40) && x > W / 3 &&
			x < (W * 2) / 3)
	{
		f->mousedown = MOUSEDOWNG_K;
		change_colour_value(f, 'g', 1, x);
		draw_stuff(f);
	}
	else if (button == MOUSEDOWN_K && y > (H - 40) && x > (W * 2) / 3 && x < W)
	{
		f->mousedown = MOUSEDOWNB_K;
		change_colour_value(f, 'b', 1, x);
		draw_stuff(f);
	}
	f->x = x;
	f->y = y;
	f->mousemove = 0;
	return (1);
}

int			mouse_press(int button, int x, int y, t_fractol *f)
{
	if (button == MOUSEDOWN_K && y > 0 && y < (H - 40) && x > 0 && x < W)
		f->mousedown = MOUSEDOWN_K;
	else if (button == MOUSEDOWN2_K && y > 0 && y < (H - 40) && x > 0 && x < W)
		f->mousedown = MOUSEDOWN2_K;
	else if (button == SCROLL_DOWN_K && y > 0 && y < (H - 40) && x > 0 && x < W)
	{
		f->zoom /= 0.9;
		if (x != W_CEN)
			f->x_offset += f->ofst_sens * ((x - W_CEN) / 6) / f->zoom;
		if (y != H_CEN)
			f->y_offset += f->ofst_sens * ((y - H_CEN) / 6) / f->zoom;
		draw_stuff(f);
	}
	else if (button == SCROLL_UP_K && y > 0 && y < (H - 40) && x > 0 && x < W)
	{
		if (f->zoom > 0.2)
		{
			f->zoom /= 1.1;
			draw_stuff(f);
		}
	}
	return (mouse_press2(button, x, y, f));
}
