/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_key_press.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 12:51:47 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 11:00:31 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	clear_col_tab(int **old_tab)
{
	free(*old_tab);
	*old_tab = NULL;
}

static int	key_press2(int k, t_fractol *f)
{
	if (k == PLUS_K || (k == MINUS_K && f->iterations != 1))
		f->iterations += (k == PLUS_K) ? 4 : -4;
	else if ((k == LESSTHAN_K && f->n_colours != 1) || k == GREATERTHAN_K)
	{
		clear_col_tab(&f->col_tab);
		(k == LESSTHAN_K) ? --f->n_colours : ++f->n_colours;
		f->col_tab = get_col_tab_smooth(f, f->col_tab);
	}
	else if (k == I_K)
		f->info_panel = (f->info_panel == 0) ? 1 : 0;
	else if (k == R_K)
	{
		f->zoom = 0.6;
		ft_setdoubletozero(&f->x_offset, &f->y_offset, NULL, NULL);
		f->const_sens = 0.03;
		f->iterations = 25;
		f->n_colours = 30;
		clear_col_tab(&f->col_tab);
		f->col_tab = get_col_tab(f, f->col_tab);
		f->real_const = get_starting_const('r', f->name);
		f->imag_const = get_starting_const('i', f->name);
	}
	draw_stuff(f);
	return (1);
}

int			key_press(int keycode, t_fractol *f)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == LEFT_K || keycode == RIGHT_K)
		f->x_offset += ((keycode == LEFT_K) ? -8 : 8) * f->ofst_sens / f->zoom;
	else if (keycode == UP_K || keycode == DOWN_K)
		f->y_offset += ((keycode == UP_K) ? -8 : 8) * f->ofst_sens / f->zoom;
	else if (keycode == SPACE_K)
		f->pause = (f->pause == 1 ? 0 : 1);
	else if (keycode == A_K)
		f->zoom /= 0.6;
	else if (keycode == S_K)
		f->zoom /= 1.4;
	else if (keycode == X_K)
		f->col_tab = get_col_tab_offset(f, f->col_tab);
	else if (keycode == C_K)
		f->col_tab = get_col_tab_smooth(f, f->col_tab);
	else if (keycode == V_K)
		f->col_tab = get_col_tab(f, f->col_tab);
	else if (keycode == B_K)
		f->col_tab = get_col_tab_random(f, f->col_tab);
	else if (keycode == ADD_K)
		f->const_sens += 0.001;
	else if (keycode == SUBTRACT_K && f->const_sens > 0.0)
		f->const_sens -= 0.001;
	return (key_press2(keycode, f));
}
