/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractalfdf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 07:22:38 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 16:34:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALFDF_H
# define FRACTALFDF_H

# include "config.h"
# include "fractal2d.h"

typedef struct	s_fractalfdf
{
	t_fractal2d	fractal;
	int			zoom;
	int			center_x;
	int			center_y;
	double		angle_x;
	double		angle_z;
	int			mouse_x;
	int			mouse_y;
	int			button_flag;
	int			shift_flag;
}				t_fractalfdf;

int				commonfdf_keyboard_press(int keycode, t_fractalfdf *conf);
int				commonfdf_key_release(int keycode, t_fractalfdf *conf);
int				commonfdf_mouse_press(int button, int x, int y,
		t_fractalfdf *conf);
int				commonfdf_mouse_release(int button, int x, int y,
		t_fractalfdf *conf);
int				commonfdf_mouse_move(int x, int y, t_fractalfdf *conf);
void			mandelfdf_initialization(t_fractalfdf *conf);
int				juliafdf_key_press(int keycode, t_fractalfdf *conf);
int				juliafdf_mouse_move(int x, int y, t_fractalfdf *conf);
void			juliafdf_initialization(t_fractalfdf *conf);

#endif
