/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 16:08:48 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 15:09:29 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	thread_stuff(t_fractol *f)
{
	t_tview		view[16];
	pthread_t	t_id[16];
	int			i;
	void		*(*frac)(void *view);

	if (f->name == 1 || f->name == 2)
		frac = (f->name == 1) ? &julia_thread : &mandelbrot_thread;
	else if (f->name == 3 || f->name == 4)
		frac = (f->name == 3) ? &circle_thread : &julia_tree_thread;
	else if (f->name == 5 || f->name == 6)
		frac = (f->name == 5) ? &forest_thread : &doom_guy_thread;
	else if (f->name == 7 || f->name == 8)
		frac = (f->name == 7) ? &exploding_star_thread : &heaven_thread;
	else if (f->name == 9 || f->name == 10)
		frac = (f->name == 9) ? &random_thread : &julia_thread;
	i = -1;
	while (++i < 16)
	{
		view[i].i = i;
		view[i].f = f;
		pthread_create(&t_id[i], NULL, frac, &view[i]);
	}
	i = -1;
	while (++i < 16)
		pthread_join(t_id[i], NULL);
}

static void	draw_info_panel(t_fractol *f, int colour)
{
	mlx_string_put(f->mlx, f->win, 10, 5, colour, LEGEND1);
	mlx_string_put(f->mlx, f->win, 435, 5, colour, ft_itoa(f->iterations));
	mlx_string_put(f->mlx, f->win, 10, 25, colour, LEGEND2);
	mlx_string_put(f->mlx, f->win, 275, 25, colour, ft_itoa(f->n_colours));
	mlx_string_put(f->mlx, f->win, 10, H - 90, colour, "-- Colour Legend --");
	mlx_string_put(f->mlx, f->win, 10, H - 70, colour, COLOUR_LEGEND);
}

int			draw_stuff(t_fractol *f)
{
	mlx_clear_window(f->mlx, f->win);
	thread_stuff(f);
	mlx_put_image_to_window(f->mlx, f->win, f->image->img, 0, 0);
	mlx_put_image_to_window(f->mlx, f->win, f->col_bars->b_ground->img,
			0, H - 40);
	mlx_put_image_to_window(f->mlx, f->win, f->col_bars->r_bar->img,
			0, H - 40);
	mlx_put_image_to_window(f->mlx, f->win, f->col_bars->g_bar->img,
			W / 3, H - 40);
	mlx_put_image_to_window(f->mlx, f->win, f->col_bars->b_bar->img,
			W * 2 / 3, H - 40);
	if (f->info_panel == 1)
		draw_info_panel(f, (f->image->pix[0] > 0x999999 ? 0 : 0xFFFFFF));
	mlx_string_put(f->mlx, f->win, (W / 6) - 20, H - 30, 0xFF0000,
			"RED");
	mlx_string_put(f->mlx, f->win, W_CEN - 20, H - 30, 0x00FF00,
			"GREEN");
	mlx_string_put(f->mlx, f->win, ((W * 5) / 6) - 20, H - 30, 0x0000FF,
			"BLUE");
	return (1);
}

t_image		*new_image(t_fractol *f, int width, int height)
{
	t_image		*image;

	image = (t_image *)malloc(sizeof(t_image));
	image->img = mlx_new_image(f->mlx, width, height);
	image->pix = (int *)mlx_get_data_addr(image->img,
			&image->bpp, &image->size_line, &image->endian);
	image->size_line /= 4;
	return (image);
}

void		set_image_pixel(t_image *im, int x, int y, unsigned int colour)
{
	im->pix[x + (y * im->size_line)] = colour;
}
