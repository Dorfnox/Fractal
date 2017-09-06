/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exploding_star.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 19:21:09 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 15:38:02 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	complex_calc(double n, double constant)
{
	return (((1.0 - n * n * n / 6.0) /
			((n - ((n * n) / 2.0)) * (n - ((n * n) / 2.0)))) + constant);
}

static void		set_tmpwh(t_ri *ri, t_fractol *f)
{
	ri->tmp_w = 0.5 * f->zoom * W;
	ri->tmp_h = 0.5 * f->zoom * H;
}

static void		set_ri(t_ri *ri, t_fractol *f, int x, int y)
{
	ri->n_r = (x - W / 2) / ri->tmp_w + f->x_offset;
	ri->n_i = (y - H / 2) / ri->tmp_h + f->y_offset;
}

static void		exploding_star(t_fractol *f, int x, int y, int ey)
{
	t_ri			ri;

	set_tmpwh(&ri, f);
	while (++y < ey)
	{
		while (++x < W)
		{
			set_ri(&ri, f, x, y);
			ri.iters = 0;
			while (ri.iters++ < f->iterations)
			{
				ri.o_r = ri.n_r;
				ri.o_i = ri.n_i;
				ri.n_r = JULIA_REAL(ri.o_r, ri.o_i);
				ri.n_i = JULIA_IMAG(ri.o_r, ri.o_i);
				ri.n_r = complex_calc(ri.n_r, f->real_const);
				ri.n_i = complex_calc(ri.n_i, f->imag_const);
				if ((ri.n_r * ri.n_r + ri.n_i * ri.n_i) > f->diameter)
					break ;
			}
			f->image->pix[x + (y * f->image->size_line)] =
				f->col_tab[ri.iters % f->n_colours];
		}
		x = -1;
	}
}

void			*exploding_star_thread(void *view)
{
	t_tview	*v;

	v = (t_tview *)view;
	exploding_star(v->f, -1, ((H / 16) * v->i) - 1, (H / 16) * (v->i + 1));
	return (NULL);
}
