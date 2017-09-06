/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 13:23:25 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 15:48:06 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			initialize_hooks(t_fractol *f)
{
	mlx_hook(f->win, 2, 0, key_press, f);
	mlx_hook(f->win, 4, 0, mouse_press, f);
	mlx_hook(f->win, 5, 0, mouse_release, f);
	mlx_hook(f->win, 6, 0, mouse_move, f);
	mlx_hook(f->win, 12, 0, draw_stuff, f);
	mlx_hook(f->win, 17, 0, exit_window, f);
}

static void			*get_new_window(void **mlx, int name)
{
	if (name == 1)
		return (mlx_new_window(*mlx, W, H, F1));
	else if (name == 2)
		return (mlx_new_window(*mlx, W, H, F2));
	else if (name == 3)
		return (mlx_new_window(*mlx, W, H, F3));
	else if (name == 4)
		return (mlx_new_window(*mlx, W, H, F4));
	else if (name == 5)
		return (mlx_new_window(*mlx, W, H, F5));
	else if (name == 6)
		return (mlx_new_window(*mlx, W, H, F6));
	else if (name == 7)
		return (mlx_new_window(*mlx, W, H, F7));
	else if (name == 8)
		return (mlx_new_window(*mlx, W, H, F8));
	else if (name == 9)
		return (mlx_new_window(*mlx, W, H, F9));
	else if (name == 10)
		return (mlx_new_window(*mlx, W, H, F10));
	return (NULL);
}

static t_fractol	*set_fractol_data(t_fractol *f, void **mlx, char *s)
{
	f->name = get_fractol_name(s);
	f->win = get_new_window(mlx, f->name);
	f->mousedown = 0;
	f->mousemove = 0;
	f->info_panel = 0;
	f->pause = 1;
	f->zoom = 0.6;
	f->iterations = 25;
	f->n_colours = 30;
	f->x = 0;
	f->y = 0;
	f->r = 20;
	f->g = 100;
	f->b = 180;
	ft_setdoubletozero(&f->x_offset, &f->y_offset, NULL, NULL);
	f->ofst_sens = 0.003;
	f->real_const = get_starting_const('r', f->name);
	f->imag_const = get_starting_const('i', f->name);
	f->const_sens = 0.03;
	f->diameter = 4;
	f->col_tab = get_col_tab(f, NULL);
	f->image = new_image(f, W, H);
	f->col_bars = get_colour_bars(f);
	initialize_hooks(f);
	return (f);
}

static t_fractol	*initialize_fractols(void **mlx, char **s)
{
	short		i;
	t_fractol	*tmp;
	t_fractol	*head;

	i = 0;
	if (!(head = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
		return (ft_putnull("Failed to malloc space for fractol"));
	head->mlx = *mlx;
	set_fractol_data(head, mlx, s[i]);
	draw_stuff(head);
	head->head = head;
	head->next = NULL;
	tmp = head;
	while (s[++i])
	{
		if (!(tmp->next = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
			return (ft_putnull("Failed to malloc space for fractol"));
		tmp->next->mlx = *mlx;
		set_fractol_data(tmp->next, mlx, s[i]);
		tmp = tmp->next;
		draw_stuff(tmp);
		tmp->head = head;
		tmp->next = NULL;
	}
	return (head);
}

int					main(int argc, char **argv)
{
	void		*mlx;
	t_fractol	*f;

	if (argc < 2 || !names_are_okay(argv))
		return (ft_puterror(USAGE, 0));
	mlx = mlx_init();
	if (!(f = initialize_fractols(&mlx, &argv[1])))
		return (ft_puterror("Fractol initialization of linked list error", 0));
	mlx_loop(mlx);
	return (1);
}
