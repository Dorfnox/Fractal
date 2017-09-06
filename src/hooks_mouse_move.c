/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 20:41:59 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/19 15:54:20 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	mouse_move2(int x, int y, t_fractol *f)
{
	if (!f->pause && (f->name != 2 && f->name != 3))
	{
		if (f->x != x)
			f->real_const += (f->x < x) ?
				f->const_sens / f->zoom : -(f->const_sens / f->zoom);
		if (f->y != y)
			f->imag_const += (f->y < y) ?
				f->const_sens / f->zoom : -(f->const_sens / f->zoom);
		draw_stuff(f);
	}
	f->x = x;
	f->y = y;
	f->mousemove = 1;
	return (1);
}

int			mouse_move(int x, int y, t_fractol *f)
{
	if (f->mousedown == MOUSEDOWN_K && y > 0 && y < (H - 40) && x > 0 && x < W)
	{
		if (f->x != x)
			f->x_offset += f->ofst_sens * (f->x - x) / f->zoom;
		if (f->y != y)
			f->y_offset += f->ofst_sens * (f->y - y) / f->zoom;
		draw_stuff(f);
	}
	else if (f->mousedown == MOUSEDOWNR_K && x >= 0 && x <= W / 3)
	{
		change_colour_value(f, 'r', 1, x);
		draw_stuff(f);
	}
	else if (f->mousedown == MOUSEDOWNG_K && x >= W / 3 && x <= (W * 2) / 3)
	{
		change_colour_value(f, 'g', 1, x);
		draw_stuff(f);
	}
	else if (f->mousedown == MOUSEDOWNB_K && x >= (W * 2) / 3 && x <= W)
	{
		change_colour_value(f, 'b', 1, x);
		draw_stuff(f);
	}
	return (mouse_move2(x, y, f));
}
