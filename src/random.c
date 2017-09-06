/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 19:21:09 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 15:38:42 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		random_frac(t_fractol *f, int x, int y, int ey)
{
	t_ri			ri;

	ri.tmp_w = 0.5 * f->zoom * W;
	ri.tmp_h = 0.5 * f->zoom * H;
	while (++y < ey)
	{
		while (++x < W)
		{
			ri.n_r = (x - W / 2) / ri.tmp_w + f->x_offset;
			ri.n_i = (y - H / 2) / ri.tmp_h + f->y_offset;
			ri.iters = 0;
			while (ri.iters++ < f->iterations)
			{
				ri.o_r = ri.n_r;
				ri.o_i = ri.n_i;
				ri.n_r = ri.o_r * 0.5 / f->real_const + ri.o_i;
				ri.n_i = (ri.o_r * ri.o_i * 3.142) - f->imag_const;
				if (ri.n_r * ri.n_r + ri.n_i * ri.n_i > f->diameter)
					break ;
			}
			f->image->pix[x + (y * f->image->size_line)] =
				f->col_tab[ri.iters % f->n_colours];
		}
		x = -1;
	}
}

void			*random_thread(void *view)
{
	t_tview	*v;

	v = (t_tview *)view;
	random_frac(v->f, -1, ((H / 16) * v->i) - 1, (H / 16) * (v->i + 1));
	return (NULL);
}
