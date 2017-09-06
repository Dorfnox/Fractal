/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helperfuncs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 22:24:08 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 15:39:07 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_fractol	*free_current_frac2(t_fractol **f)
{
	t_fractol	*new_head;
	t_fractol	*tmp;

	if ((tmp = (*f)->head ? (*f)->head : NULL))
	{
		if (*f == (*f)->head)
		{
			new_head = (*f)->next;
			while (tmp)
			{
				tmp->head = new_head;
				tmp = tmp->next;
			}
		}
		else
		{
			while (tmp->next != *f)
				tmp = tmp->next;
			tmp->next = (!((*f)->next)) ? NULL : (*f)->next;
		}
		tmp = (*f)->head;
		free(*f);
	}
	return (tmp);
}

t_fractol			*free_current_frac(t_fractol **f)
{
	mlx_destroy_image((*f)->mlx, (*f)->image->img);
	mlx_destroy_image((*f)->mlx, (*f)->col_bars->r_bar->img);
	mlx_destroy_image((*f)->mlx, (*f)->col_bars->b_bar->img);
	mlx_destroy_image((*f)->mlx, (*f)->col_bars->g_bar->img);
	mlx_destroy_image((*f)->mlx, (*f)->col_bars->b_ground->img);
	free((*f)->image);
	free((*f)->col_bars->r_bar);
	free((*f)->col_bars->g_bar);
	free((*f)->col_bars->b_bar);
	free((*f)->col_bars->b_ground);
	free((*f)->col_bars);
	free((*f)->col_tab);
	mlx_destroy_window((*f)->mlx, (*f)->win);
	return (free_current_frac2(f));
}

unsigned int		get_fractol_name(const char *s)
{
	short	ret;

	ret = 0;
	ret = (!ret && (ft_strequ(s, "1") || ft_strequ(s, F1))) ? 1 : ret;
	ret = (!ret && (ft_strequ(s, "2") || ft_strequ(s, F2))) ? 2 : ret;
	ret = (!ret && (ft_strequ(s, "3") || ft_strequ(s, F3))) ? 3 : ret;
	ret = (!ret && (ft_strequ(s, "4") || ft_strequ(s, F4))) ? 4 : ret;
	ret = (!ret && (ft_strequ(s, "5") || ft_strequ(s, F5))) ? 5 : ret;
	ret = (!ret && (ft_strequ(s, "6") || ft_strequ(s, F6))) ? 6 : ret;
	ret = (!ret && (ft_strequ(s, "7") || ft_strequ(s, F7))) ? 7 : ret;
	ret = (!ret && (ft_strequ(s, "8") || ft_strequ(s, F8))) ? 8 : ret;
	ret = (!ret && (ft_strequ(s, "9") || ft_strequ(s, F9))) ? 9 : ret;
	ret = (!ret && (ft_strequ(s, "10") || ft_strequ(s, F10))) ? 10 : ret;
	return (ret);
}

int					names_are_okay(char **s)
{
	short	i;

	i = 1;
	while (s[i])
		if (!get_fractol_name(s[i++]))
			return (0);
	return (1);
}

double				get_starting_const(char real_or_imag, unsigned int name)
{
	if (real_or_imag == 'r')
	{
		if (name == 4)
			return (-0.016);
		if (name == 8)
			return (0.235786);
		return (-0.835);
	}
	else if (real_or_imag == 'i')
	{
		if (name == 4)
			return (0.2979);
		if (name == 8)
			return (-0.036142);
		return (-0.2321);
	}
	return (0.0);
}
