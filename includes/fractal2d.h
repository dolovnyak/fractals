/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal2d.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 07:23:10 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/15 17:44:53 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL2D_H
# define FRACTAL2D_H

# include "config.h"

typedef struct	s_fractal2d
{
	double	left_b;
	double	right_b;
	double	top_b;
	double	bot_b;
	double	radius;
	double	const_real;
	double	const_imagin;
	int		depth;
	int		color_mult;
	t_cl	*cl;
	t_mlx	*mlx;
	int		center_x;
	int		center_y;
	int		mouse_move_flag;
}				t_fractal2d;

typedef struct	s_roots
{
	t_complex	root1;
	t_complex	root2;
	t_complex	root3;
	t_complex	root4;
	t_complex	root5;
}				t_roots;

int				common2d_key_press(int keycode, t_fractal2d *conf);
int				common2d_mouse_press(int button, int x, int y,
		t_fractal2d *conf);
void			mandel2d_initialization(t_fractal2d *conf);
void			julia2d_initialization(t_fractal2d *conf);
int				julia2d_mouse_move(int x, int y, t_fractal2d *conf);
int				julia2d_key_press(int keycode, t_fractal2d *conf);
void			burning_ship2d_initialization(t_fractal2d *conf);
void			newton_initialization(t_fractal2d *conf);
void			fractal_dick_initialization(t_fractal2d *conf);

#endif
