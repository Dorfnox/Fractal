/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 14:44:00 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 15:39:31 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_to_zero(double *a, double *b, unsigned int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static void	mandelbrot(t_fractol *f, int x, int y, int ey)
{
	t_ri	ri;

	ri.tmp_w = 0.5 * f->zoom * W;
	ri.tmp_h = 0.5 * f->zoom * H;
	while (++y < ey)
	{
		while (++x < W)
		{
			ri.mand_r_const = (x - W / 2) / ri.tmp_w + f->x_offset;
			ri.mand_i_const = (y - H / 2) / ri.tmp_h + f->y_offset;
			set_to_zero(&ri.n_r, &ri.n_i, &ri.iters);
			while (ri.iters++ < f->iterations)
			{
				ri.o_r = ri.n_r;
				ri.o_i = ri.n_i;
				ri.n_r = MAND_REAL(ri.o_r, ri.o_i);
				ri.n_i = MAND_IMAG(ri.o_r, ri.o_i);
				if ((ri.n_r * ri.n_r + ri.n_i * ri.n_i) > f->diameter)
					break ;
			}
			f->image->pix[x + (y * f->image->size_line)] =
				f->col_tab[ri.iters % f->n_colours];
		}
		x = -1;
	}
}

void		*mandelbrot_thread(void *view)
{
	t_tview	*v;

	v = (t_tview *)view;
	mandelbrot(v->f, -1, ((H / 16) * v->i) - 1, (H / 16) * (v->i + 1));
	return (NULL);
}
