/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelfdf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 09:41:39 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/07 10:55:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDELFDF_H
# define MANDELFDF_H

#include "config.h"

typedef struct	s_mandelfdf
{
	double      left_b;
	double      right_b;
	double      top_b;
	double      bot_b;
	int         depth;
	int         zoom;
	int			center_x;
	int			center_y;
	double      angle_x;
	double      angle_z;
	int         mouse_x;
	int         mouse_y;
	int         button_flag;
	int         control_flag;
	int			color_mult;
	t_mlx		*mlx;
	t_cl		*cl;
}				t_mandelfdf;

void	mandelfdf_initialization(t_mandelfdf *conf);
int     mandelfdf_keyboard_press(int keycode, t_mandelfdf *conf);
int     mandelfdf_key_release(int keycode, t_mandelfdf *conf);
int     mandelfdf_mouse_press(int button, int x, int y, t_mandelfdf *conf);
int     mandelfdf_mouse_release(int button, int x, int y, t_mandelfdf *conf);
int     mandelfdf_mouse_move(int x, int y, t_mandelfdf *conf);

#endif
