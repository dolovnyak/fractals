/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:46:07 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/03 02:45:42 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <OPENCL/opencl.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "utilits.h"
# include "math_vec.h"
# include "fractal.h"
# include "RTv1.h"
# include <stdio.h>

typedef struct	s_cl
{
	cl_command_queue	queue;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel_mandel;
	cl_kernel			kernel_rt;
}				t_cl;

typedef struct  s_mlx
{
	void    *img_ptr;
	void    *mlx;
	void    *win;
	char    *img_data;
	int     bpp;
	int     endian;
	int     size_line;
	int     width;
	int     height;
}               t_mlx;

typedef struct  s_config
{
	int         lights_num;
	int         objects_num;
	t_object3d  *objects;
	t_lights	*lights;
	t_canvas    canvas;
	t_mlx       mlx;
	t_cl		cl;
	t_fractal	fractal;
}               t_conf;

void			initialization_mlx(t_mlx *mlx);
void			initialization_canvas(t_canvas *canvas);
void			initialization_scene(t_conf *conf);
void			initialization_cl(t_cl *cl);
void			initialization_fractal(t_fractal *fractal);
int				get_num_objects(t_fractal_point **all_points, int xy_len, int z_len);
void			get_objects(t_conf *conf, t_fractal_point **all_spheres, int xy_len, int z_len);
t_fractal_point	**get_fractal(t_conf *conf, size_t global_size);
int				key_press(int key, t_conf *conf);
int				exit_event(t_conf *conf);
int				refresh(t_conf *conf);
void			ft_exit(t_conf *conf);

#endif
