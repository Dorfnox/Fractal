/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 13:15:39 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 15:40:03 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "fractol_macros.h"
# include <math.h>
# include <mlx.h>
# include <pthread.h>

# define F1 "Julia"
# define F2 "Mandelbrot"
# define F3 "Circle"
# define F4 "Julia Tree"
# define F5 "Forest"
# define F6 "Doom Guy"
# define F7 "Exploding Star"
# define F8 "Heaven"
# define F9 "Random"
# define F10 "Non-existant"

# define W 600
# define H 600
# define W_CEN W / 2
# define H_CEN H / 2

typedef struct			s_image
{
	void				*img;
	int					*pix;
	int					bpp;
	int					size_line;
	int					endian;
}						t_image;

typedef struct			s_col_bars
{
	struct s_image		*r_bar;
	struct s_image		*g_bar;
	struct s_image		*b_bar;
	struct s_image		*b_ground;
}						t_col_bars;

typedef struct			s_colours
{
	double				r;
	double				g;
	double				b;
}						t_colours;

typedef struct			s_ri
{
	double				mand_r_const;
	double				mand_i_const;
	double				tmp_w;
	double				tmp_h;
	double				o_r;
	double				o_i;
	double				n_r;
	double				n_i;
	unsigned int		iters;
}						t_ri;

typedef struct			s_fractol
{
	unsigned int		name:4;
	unsigned int		mousedown:4;
	unsigned int		mousemove:2;
	unsigned int		info_panel:1;
	unsigned int		pause:1;
	unsigned int		iterations;
	unsigned int		n_colours;
	unsigned int		r:8;
	unsigned int		g:8;
	unsigned int		b:8;
	unsigned short		x;
	unsigned short		y;
	void				*mlx;
	void				*win;
	double				zoom;
	double				x_offset;
	double				y_offset;
	double				ofst_sens;
	double				real_const;
	double				imag_const;
	double				const_sens;
	double				diameter;
	int					*col_tab;
	struct s_image		*image;
	struct s_col_bars	*col_bars;
	struct s_fractol	*head;
	struct s_fractol	*next;
}						t_fractol;

typedef struct			s_tview
{
	int					i;
	t_fractol			*f;
}						t_tview;

/*
** main.c
*/

int						exit_window(t_fractol *f);

/*
** hooks.c
*/

int						mouse_move(int x, int y, t_fractol *f);
int						mouse_release(int button, int x, int y, t_fractol *f);
int						mouse_press(int button, int x, int y, t_fractol *f);
int						key_press(int keycode, t_fractol *f);

/*
** images.c
*/

int						draw_stuff(t_fractol *f);
t_image					*new_image(t_fractol *f, int width, int height);
void					set_image_pixel(t_image *im, int x, int y,
						unsigned int colour);

/*
** color_bars.c
*/

void					*new_bar_image(t_fractol *f, int w, int h,
						unsigned int col);
t_col_bars				*get_colour_bars(t_fractol *f);
void					change_colour_value(t_fractol *f, char rgb,
						int s, int x);

/*
** colors.c
*/

int						*int_table(int size);
int						rgb_to_hex(short r, short g, short b);
int						*get_col_tab(t_fractol *f, int *old_tab);
int						*get_col_tab_smooth(t_fractol *f, int *old_tab);
int						*get_col_tab_offset(t_fractol *f, int *old_tab);
int						*get_col_tab_random(t_fractol *f, int *old_tab);

/*
** helperfuncs.c
*/

t_fractol				*free_current_frac(t_fractol **f);
unsigned int			get_fractol_name(const char *s);
int						names_are_okay(char **s);
double					get_starting_const(char real_or_imag,
						unsigned int name);

/*
** {julia, mandelbrot, circle, julia_tree, forest, doom_guy, heaven}.c
*/

void					*julia_thread(void *view);
void					*mandelbrot_thread(void *view);
void					*circle_thread(void *view);
void					*julia_tree_thread(void *view);
void					*forest_thread(void *view);
void					*doom_guy_thread(void *view);
void					*exploding_star_thread(void *view);
void					*heaven_thread(void *view);
void					*random_thread(void *view);

#endif
