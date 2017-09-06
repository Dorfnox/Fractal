/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_macros.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 11:55:35 by bpierce           #+#    #+#             */
/*   Updated: 2017/08/20 15:26:20 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_MACROS_H
# define FRACTOL_MACROS_H

/*
** Keys
*/

# define A_K 0
# define B_K 11
# define C_K 8
# define D_K 2
# define E_K 14
# define F_K 3
# define G_K 5
# define H_K 4
# define I_K 34
# define J_K 38
# define K_K 40
# define L_K 37
# define M_K 46
# define N_K 45
# define O_K 31
# define P_K 35
# define Q_K 12
# define R_K 15
# define S_K 1
# define T_K 17
# define U_K 32
# define V_K 9
# define W_K 13
# define X_K 7
# define Y_K 16
# define Z_K 6
# define UP_K 126
# define DOWN_K 125
# define RIGHT_K 124
# define LEFT_K 123
# define MOUSEDOWN_K 1
# define MOUSEDOWN2_K 2
# define SCROLL_UP_K 4
# define SCROLL_DOWN_K 5
# define MOUSEDOWNR_K 6
# define MOUSEDOWNG_K 7
# define MOUSEDOWNB_K 8
# define SPACE_K 49
# define PLUS_K 69
# define MINUS_K 78
# define ADD_K 24
# define SUBTRACT_K 27
# define LESSTHAN_K 43
# define GREATERTHAN_K 47

/*
** Julia Macros
** equation is:     z = p^2 + c
** In other words:  new_real_location = old_real_location^2 + real_constant
** And for imag:	new_imag_location = old_imag_location^2 + imag_constant
*/

# define JULIA_REAL(ore, oim) (ore * ore - oim * oim + f->real_const)
# define JULIA_IMAG(ore, oim) (2 * ore * oim + f->imag_const)

/*
** Mandelbrot Macros
** equation is:     z = p^2 + c
** In other words:  new_real_location = old_real_location^2 + real_constant
** And for imag:	new_imag_location = old_imag_location^2 + imag_constant
*/

# define MAND_REAL(ore, oim) (ore * ore - oim * oim + ri.mand_r_const)
# define MAND_IMAG(ore, oim) (2 * ore * oim + ri.mand_i_const)

/*
** Circle Macros
** equation is:     z = p^2
** In other words:  new_real_location = old_real_location^2
** And for imag:	new_imag_location = old_imag_location^2
*/

# define CIRC_REAL(ore, oim) (ore * ore - oim * oim)
# define CIRC_IMAG(ore, oim) (2 * ore * oim)

/*
** Julia Tree Macro
*/

# define JULIA_TREE(ore, oim) (2 * fabs(ore * oim) + f->imag_const)

/*
** Heaven Macro
*/

# define H_REAL(ore, oim) (ore - 0.23 * ore / 1.3 - oim * oim + f->real_const)
# define H_IMAG(ore, oim) (1.7 * ore * oim + f->imag_const)

/*
** String macros
*/

# define USAGE1 "usage: enter 'fractol' with a proper fractol name:\n"
# define USAGE2 "- '"F1"' or '1'\n- '"F2"' or '2'\n- '"F3"' or '3'\n"
# define USAGE3 "- '"F4"' or '4'\n- '"F5"' or '5'\n- '"F6"' or '6'\n"
# define USAGE4 "- '"F7"' or '7'\n- '"F8"' or '8'\n- '"F9"' or '9'\n"
# define USAGE USAGE1 USAGE2 USAGE3 USAGE4 "     <(^_^)>"

# define LEGEND1 "Number of Iterations (numpad -, numpad +):"
# define LEGEND2 "Number of Colours (< , >):"
# define COLOUR_LEGEND "X: Offset  C: Basic  V: Variety  B: Random"

#endif
