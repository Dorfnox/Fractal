/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 15:52:19 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 09:48:08 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			exit_window(t_fractol *f)
{
	if (!(free_current_frac(&f)))
		exit(0);
	return (1);
}

int			mouse_release(int button, int x, int y, t_fractol *f)
{
	if (!f->mousemove && y > 0 && y < (H - 40) && x > 0 && x < W)
	{
		if (button == MOUSEDOWN_K)
		{
			f->zoom /= 0.7;
			if (x != W_CEN)
				f->x_offset += f->ofst_sens * ((x - W_CEN) / 1.7) / f->zoom;
			if (y != H_CEN)
				f->y_offset += f->ofst_sens * ((y - H_CEN) / 1.7) / f->zoom;
			draw_stuff(f);
		}
		else if (button == MOUSEDOWN2_K)
		{
			if (f->zoom > 0.2)
			{
				f->zoom /= 1.3;
				draw_stuff(f);
			}
		}
	}
	f->mousedown = 0;
	f->mousemove = 0;
	return (1);
}
