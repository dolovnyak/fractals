/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel2d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 09:42:04 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 09:59:39 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDEL2D_H
# define MANDEL2D_H

# include "config.h"

typedef struct	s_mandel2d
{
	double      left_b;
	double      right_b;
	double      top_b;
	double      bot_b;
	int         depth;
	int         color_mult;
	cl_kernel	kernel_mandel;
	t_cl		*cl;
	t_mlx		*mlx;
}				t_mandel2d;

int		mandel2d_mouse_press(int button, int x, int y, t_mandel2d *conf);
int     mandel2d_keyboard_event(int keycode, t_mandel2d *conf);
void	mandel2d_initialization(t_mandel2d *conf);

#endif
