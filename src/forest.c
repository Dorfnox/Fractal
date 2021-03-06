/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 19:21:09 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 10:27:26 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	forest(t_fractol *f, int x, int y, int ey)
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
				ri.n_r = f->real_const * log(ri.o_r * ri.o_r);
				ri.n_i = f->imag_const * log(ri.o_i * ri.o_i);
				if ((ri.n_r * ri.n_r + ri.n_i * ri.n_i) > f->diameter)
					break ;
			}
			f->image->pix[x + (y * f->image->size_line)] =
				f->col_tab[ri.iters % f->n_colours];
		}
		x = -1;
	}
}

void		*forest_thread(void *view)
{
	t_tview	*v;

	v = (t_tview *)view;
	forest(v->f, -1, ((H / 16) * v->i) - 1, (H / 16) * (v->i + 1));
	return (NULL);
}
