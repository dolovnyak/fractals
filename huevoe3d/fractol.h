/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:08:09 by sbecker           #+#    #+#             */
/*   Updated: 2019/04/03 06:17:32 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include <OPENCL/opencl.h>
# include <stdio.h>

# define PROGRAM_FILE "fractolCL.cl"

typedef struct  s_all
{
	void		*img_ptr;
	void		*mlx;
	void		*win;
	char		*img_data;
	int     	bpp;
	int			endian;
	int			size_line;
	int     	s_width;
	int     	s_height;
	int			center_x;
	int			center_y;
	int			zoom;
	int			relation_x;
	int			relation_y;
	double		left_b;
	double		right_b;
	double		top_b;
	double		bot_b;
	double		front_b;
	double		rear_b;
	int			depth;
	int			color_mult;
	cl_command_queue	queue;
	cl_context			context;
	cl_kernel			kernel;
	double		angle_x;
	double		angle_z;
	int			mouse_x;
	int			mouse_y;
	int			button_flag;
	int			control_flag;
}               t_all;

int				keyboard_event(int keycode, t_all *all);
int				mouse_event(int button, int x, int y, t_all *all);
int				mouse_move(int x, int y, t_all *all);
int				mouse_release(int button, int x, int y, t_all *all);
int				key_release(int keycode, t_all *all);
int				exit_event(void *param);
void			initialization_all(t_all *all);
void			initialization_Cl(t_all *all);

#endif
