/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_guy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 19:21:09 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 10:26:55 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_to_zero(double *a, double *b, unsigned int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static void	doom_guy(t_fractol *f, int x, int y, int ey)
{
	t_ri			ri;

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
				ri.n_r = (ri.o_r * ri.o_i) * 2 - ri.mand_r_const;
				ri.n_i = (ri.o_i * ri.o_i) * 0.4 - ri.o_i + ri.mand_i_const;
				if ((ri.n_r * ri.n_r + ri.n_i * ri.n_i) > f->diameter)
					break ;
			}
			f->image->pix[x + (y * f->image->size_line)] =
				f->col_tab[ri.iters % f->n_colours];
		}
		x = -1;
	}
}

void		*doom_guy_thread(void *view)
{
	t_tview	*v;

	v = (t_tview *)view;
	doom_guy(v->f, -1, ((H / 16) * v->i) - 1, (H / 16) * (v->i + 1));
	return (NULL);
}
